﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using cn.edu.suda.sumcu.iot;
using System.Management;
using System.Runtime.InteropServices;
using MySql.Data.MySqlClient;

namespace SerialPort
{
    ///-----------------------------------------------------------------------------------
    ///FrmMain :KW01-A1工程的窗体                                                          
    ///目    的:
    ///日    期:                                             
    ///编 程 者:
    ///-----------------------------------------------------------------------------------
    public partial class FrmMain : Form
    {      
        //1. 窗体类的临时变量区
        //private System.IO.Ports.SerialPort UARTport;   //声明系统工具-串口对象的变量声明
        //private Uart uart1;                          //声明一个自定义的Uart类型（串口操作）的变量
        //private PCNode pcNode1;                      //声明一个自定义的PCNode类型的变量
        private EMUART emuart = EMUART.getInstance();
        SCI sci;    //要调用SCI类中所定义的函数
        byte[] recvData = new byte[100];
        private byte data_num = 0;
        public struct shakeData
        {
            // SizeConst用来定义数组大小
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 25)]
            public byte[] uecomType;          //通信模组类型
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
            public byte[] mcuType;            //MCU类型
            public uint uStartAds;            //User程序起始地址
            public uint uCodeSize;            //User程序总代码大小
            public uint replaceNum;           //替换更新最大字节
            public uint reserveNum;           //保留更新最大字节（不等于0意味着有User程序）
        }
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
        public struct newshakeData
        {
            // SizeConst用来定义数组大小
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 25)]
            public byte[] uecomType;          //通信模组类型
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
            public byte[] mcuType;            //MCU类型
            public uint uStartAds;            //User程序起始地址
            public uint uCodeSize;            //User程序总代码大小
            public uint replaceNum;           //替换更新最大字节
            public uint reserveNum;           //保留更新最大字节（不等于0意味着有User程序）
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
            public byte[] BIOSVersion;            //BIOS版本号
        }
        private newshakeData newshakedata;
        //private shakeData shakedata;
        private string uecomType;   //通信模组类型
        private string mcuType;     //MCU类型
       // private string lastSelect;  //保存上一次下拉框的文本

        //2. 构造函数（启动窗体最先执行程序）
        public FrmMain()
        {
            //系统生成的构造函数（初始化窗体的元素）
            InitializeComponent();        
            //禁止检测跨线程调用异常(
            CheckForIllegalCrossThreadCalls = false;           
       }

        private object bytesToStruct(byte[] bytes, Type type)
        {
            //（1）变量声明
            int size;
            object obj;
            IntPtr structPtr;

            size = Marshal.SizeOf(type);
            //（2）判断字节长度
            if (size > bytes.Length) return null;
            //（3）分配结构体内存空间
            structPtr = Marshal.AllocHGlobal(size);
            //（4）将byte数组拷贝到分配好的内存空间
            Marshal.Copy(bytes, 0, structPtr, size);
            //（5）将内存空间转换为目标结构体
            obj = Marshal.PtrToStructure(structPtr, type);
            //（6）释放内存空间
            Marshal.FreeHGlobal(structPtr);
            return obj;
        }



        //3. 加载窗体事件程序（在构造函数之后执行的程序）
        private void FrmMain_Load(object sender, EventArgs e)
        {
            //btnCheckPcNode_Click(sender, e);                       
        }

        //========================以下是本窗体的各个事件响应函数==========================
       
        //------------------------单击“检测PC节点”按钮----------------------------------
        private void btnCheckPcNode_Click(object sender, EventArgs e)
        {        
            //int ret;            //返回值
            //string com = "";    //串口信息
            string sTemp = "";
            //byte[] recv = null;//保存串口接收信息
            //byte[] shake = { (byte)10, (byte)'s', (byte)'h', (byte)'a', (byte)'k', (byte)'e' }; //与终端握手帧数据

            byte[] userShake = { (byte)11, (byte)'a', (byte)'u', (byte)'a', (byte)'r', (byte)'t', (byte)'?' }; //与终端握手帧数据
            //byte[] send = { (byte)'S' };

            string[] SCIPorts;
            SCIPorts = SCI.SCIGetPorts();

            this.Refresh();                     //刷新显示  

            //if (emuart._Uartport != null) emuart._Uartport.Close();
            //Thread.Sleep(10);   //等待串口关闭
            //emuart = EMUART.getInstance();    //每次“重新连接”重新实例化
            //ret = emuart.findDevice(out com, 115200);  //寻找emuart设备
            //this.lbl_PC_Node_State.Text = com;       //右上角显示区

            //if (ret == 1) goto btn_uartcheck_Click_EXIT1;
            ////（4.2）找到串口，没有找到UE，退出函数
            //else if (ret == 2) goto btn_uartcheck_Click_EXIT2;
            //emuart.bufferClear();   //清除接收数组缓冲区
            //emuart.send(shake, out recv, 200, 3); //获得设备的信息在recv中
            //if (recv == null) goto btn_uartcheck_Click_EXIT3;  //没有接收到设备返回消息

            //if (recv.Length == Marshal.SizeOf(typeof(shakeData)))
            //{
            //    //byte数组转结构体
            //    shakedata = (shakeData)bytesToStruct(recv, typeof(shakeData));
            //    //获取握手帧数据
            //    uecomType = Encoding.Default.GetString(shakedata.uecomType).Replace("\0", "");
            //    mcuType = Encoding.Default.GetString(shakedata.mcuType).Replace("\0", "");

            //    //设置设备信息                   
            //    sTemp = com + "：" + uecomType + " " + mcuType;  //设备信息
            //    //状态提示
            //    this.lbl_PC_Node_State.Text = sTemp;     //右上角显示区
            //    this.btnPnFlashErase.Enabled = true;
            //    this.btnPnFlashRead.Enabled = true;
            //    this.btnPnFlashReadAddr.Enabled = true;
            //    this.btnPnFlashWrite.Enabled = true;

            //}
            //else if (recv.Length == Marshal.SizeOf(typeof(newshakeData)))
            //{
                int i;
                //byte数组转结构体
                //newshakedata = (newshakeData)bytesToStruct(recv, typeof(newshakeData));
                ////获取握手帧数据
                //uecomType = Encoding.Default.GetString(newshakedata.uecomType).Replace("\0", "");
                //mcuType = Encoding.Default.GetString(newshakedata.mcuType).Replace("\0", "");
                //设置设备信息                   
                //sTemp = com + "：" + uecomType + " " + mcuType;  //设备信息
                if (sci != null && sci.IsOpen)
                    sci.Close();

                //发送全局变量_SendByteArray中的数据,并返回结果
                for (i = 0; i < SCIPorts.Length; i++)
                {
                    //if (SCIPorts[i] == com) continue;

                    sci = new SCI(SCIPorts[i], 115200);
                    if (sci.SCIOpen())
                    {
                        //sci.SCISendData(ref send);           //发送与Uart_User串口握手的数据信息
                        sci.SCISendFrameData(ref userShake);

                        Thread.Sleep(500);
                        if (sci.SCIReceiveData(ref recvData))
                        {
                            //MessageBox.Show(System.Text.Encoding.Default.GetString(recvData));

                            //if (recvData.Length == 0 || !System.Text.Encoding.Default.GetString(recvData).Contains("Yes,I am an emuart!!"))
                            //{
                            //    this.tb_statue.Text = "未找到终端设备";
                            //    //this.lbl_PC_Node_State.Text = "未找到终端设备";

                            //    MessageBox.Show("检查UART_User(KL36:UART0)串口有无接好");

                            //    this.btnPnFlashErase.Enabled = false;
                            //    this.btnPnFlashRead.Enabled = false;
                            //    this.btnPnFlashReadAddr.Enabled = false;
                            //    this.btnPnFlashWrite.Enabled = false;
                            //    sci.Close();
                            //    continue;
                            //}
                            if (System.Text.Encoding.Default.GetString(recvData).Contains("Yes,I am an emuart!!"))   //记录UART_User串口的Com号
                            {
                                string retInfo = System.Text.Encoding.Default.GetString(recvData);
                                this.tb_statue.Text = "找到终端设备";
                                //this.lbl_PC_Node_State.Text = "连接终端在" + PublicVar.g_SCIComNum;
                                PublicVar.g_SCIComNum = SCIPorts[i];
                                
                                this.btnPnFlashErase.Enabled = true;
                                this.btnPnFlashRead.Enabled = true;
                                this.btnPnFlashReadAddr.Enabled = true;
                                this.btnPnFlashWrite.Enabled = true;
                            //sTemp = retInfo.Substring(retInfo.IndexOf('.') + 1, retInfo.Length - retInfo.IndexOf('.') - 1);
                            //sTemp = retInfo.Substring(retInfo.IndexOf('!') + 2, retInfo.Length - retInfo.IndexOf('!') - 2);
                            sTemp = retInfo.Substring(retInfo.IndexOf('!') + 2, 19);
                            //sTemp = retInfo.Substring(retInfo.IndexOf('.') + 1, retInfo.Length - retInfo.IndexOf('.') - 1);
                            this.lbl_PC_Node_State.Text = SCIPorts[i] + "：" + sTemp;     //右上角显示区

                                //this.lbl_PC_Node_State.Text = sTemp;     //右上角显示区
                                break;                                                              //找到后UART_User串口后，跳出循环

                            }
                        }
                    }
                }
                if(i == SCIPorts.Length)
                {
                    this.tb_statue.Text = "未找到终端设备";
                    MessageBox.Show("检查UART_User(KL36:UART0)串口有无接好");
                    this.btnPnFlashErase.Enabled = false;
                    this.btnPnFlashRead.Enabled = false;
                    this.btnPnFlashReadAddr.Enabled = false;
                    this.btnPnFlashWrite.Enabled = false;
                    sci.Close();
                  }
                //状态提示

            //}
            //else goto btn_uartcheck_Click_EXIT3;  //接收到错误返回
            ////(5)退出区
            ////(5.1)退出函数
            //btn_uartcheck_Click_EXIT:
            //    btnCheckPcNode.Enabled = true;
            //    return;

            ////(5.2)不存在可用串口
            //btn_uartcheck_Click_EXIT1:
            //    btnCheckPcNode.Text = "运行状态：当前不存在可用串口";  //右上角提示区
            //    this.btnPnFlashErase.Enabled = false;
            //    this.btnPnFlashRead.Enabled = false;
            //    this.btnPnFlashReadAddr.Enabled = false;
            //    this.btnPnFlashWrite.Enabled = false;
            //    goto btn_uartcheck_Click_EXIT;

            ////(5.3)存在串口，但不存在emuar设备
            //btn_uartcheck_Click_EXIT2:
            //    emuart.terminate(115200); //发送数据给终端设备，让终端设备清空其数据缓冲区
            //    btnCheckPcNode.Text = "重新连接";  //连接按键文本
            //    lbl_PC_Node_State.Text = "运行状态：已连接串口" + com + "但未找到设备";   //右上角提示区
            //    this.btnPnFlashErase.Enabled = false;
            //    this.btnPnFlashRead.Enabled = false;
            //    this.btnPnFlashReadAddr.Enabled = false;
            //    this.btnPnFlashWrite.Enabled = false;
            //    goto btn_uartcheck_Click_EXIT;

            //(5.4)没有正确接收到设备返回消息
            //btn_uartcheck_Click_EXIT3:
            //    emuart.terminate(115200); //发送数据给终端设备，让终端设备清空其数据缓冲区
            //    btnCheckPcNode.Text = "重新连接";   //连接按钮文本
            //    lbl_PC_Node_State.Text = "找到GEC在" + com + "但握手失败，请再次单击[重新连接]按钮";   //右上角提示区
            //    this.btnPnFlashErase.Enabled = false;
            //    this.btnPnFlashRead.Enabled = false;
            //    this.btnPnFlashReadAddr.Enabled = false;
            //    this.btnPnFlashWrite.Enabled = false;
            //    goto btn_uartcheck_Click_EXIT;
        }

        //--------------------------单击窗口关闭“X”按钮---------------------------------
        private void FrmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            //if (uart1 == null) return;
            ////如果串口未关闭，则关闭
            //if (uart1.IsOpen) uart1.close(); 
        }
        
        
        //-------------------------------串口接收事件的响应函数---------------------------
        private void UARTport_recvData(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            //string s1 = string.Empty;

            //Thread.Sleep(100);
            //PublicVar.g_ReceiveByteArray = sci.recvData();    //调用串口接收函数
            //if (PublicVar.g_ReceiveByteArray.Length > 0)
            //{
            //    string str = System.Text.Encoding.Default.GetString(PublicVar.g_ReceiveByteArray);
            //    this.Txt_recv2.Text = "Interrupt--- " + System.Text.Encoding.Default.GetString(PublicVar.g_ReceiveByteArray);
            //}
        }

        //---------------------------单击“读测试（逻辑地址）”按钮----------------------------
        private void btnPnFlashRead_Click(object sender, EventArgs e)
        {
            byte sector;        //扇区号
            int whi;         //偏移量
            byte n;             //读取字节数
            int i;
            byte len;
            // 2. 临时变量赋值tbOffset2

            sector = Convert.ToByte(tbSector1.Text);  // 将TextBox中的Text转换为Byte类型
            //if (sector > 63 || sector < 55)
            //{
            //    MessageBox.Show("请输入正确扇区号！");
            //    return;
            //}
            whi = Convert.ToInt32(tbOffset1.Text);   // 将TextBox中的Text转换为Byte类型
            sector = (byte) (sector + whi);
            n = Convert.ToByte(tbCount1.Text);


            byte[] SendByteArray = new byte[5];

            this.Txt_recv1.Text = "";
            this.Txt_recv2.Text = "";
            this.Txt_recv1.Refresh();
            this.Txt_recv2.Refresh();

            this.tb_statue.Text = "运行状态：" + "单击“终端UE Flash 逻辑读测试”按钮...";
            this.tb_statue.Refresh();

            try
            {

                SendByteArray[0] = (byte)'r';
                SendByteArray[1] = sector;         //第几页
                SendByteArray[2] = (byte)(0 / 256);    //偏移量高字节
                SendByteArray[3] = (byte)(0 % 256);     //偏移量低字节
                SendByteArray[4] = n;              //写入字节数

                //发送、接收、显示
                //sci.SCISendData(ref SendByteArray);
               bool  flag=sci.SCISendFrameData(ref SendByteArray);

                Thread.Sleep(500);
                if (sci.SCIReceiveData(ref recvData))
                {
                    //MessageBox.Show(Encoding.Default.GetString(recvData));

                    string str = null;
                    this.Txt_recv2.Text = Encoding.Default.GetString(recvData);
                    for (int j = 0; j < recvData.Length; j++)
                    {
                        str += recvData[j].ToString("X2");
                        str += "-";
                    }
                    this.Txt_recv1.Text = str;    //16进制字符串 
                }
            }
            catch
            {
                this.Txt_recv1.Text = "终端UE Flash读取写入失败,检查UART_User串口连接是否成功！";
            } 
        }

        //---------------------------单击“读测试（物理地址）”按钮-----------------------
        private void btnPnFlashReadAddr_Click(object sender, EventArgs e)
        {
            // 1. 临时变量声明
            int addr;            // 偏移量
            byte count;            // 读取字节数

            byte[] SendByteArray = new byte[6];          // 定义发送缓冲区
            byte offset_3, offset_2, offset_1, offset_0;                // 定义偏移地址的高低字节

            // 2. 临时变量赋值
            //sector = Convert.ToByte(tbSector1.Text);    // 将TextBox中的Text转换为Byte类型
            addr = Convert.ToInt32(tbAddr.Text,16);  // 将TextBox中的Text转换为Byte类型
            //if (addr<26624||addr>65536)
            //{
            //    MessageBox.Show("请输入合法地址！");
            //    return;
            //}
            count = Convert.ToByte(tbCountaddr.Text);

            // 计算偏移地址高低位
            offset_0 = (byte)(0xff & addr);
            offset_1 = (byte)((0xff00 & addr) >> 8);
            offset_2 = (byte)((0xff0000 & addr) >> 16);
            offset_3 = (byte)((0xff000000 & addr) >> 24);

            this.Txt_recv1.Text = "";
            this.Txt_recv2.Text = "";
            this.Txt_recv1.Refresh();
            this.Txt_recv2.Refresh();

            this.tb_statue.Text = "运行状态：" + "单击“终端UE Flash 按物理地址读测试”按钮...";
            this.tb_statue.Refresh();
            try
            {

                SendByteArray[0] = (byte)'a';      //FLASH命令，物理地址读
             
                SendByteArray[1] = offset_3;       //（物理地址）偏移量高字节
                SendByteArray[2] = offset_2;       //偏移量高字节
                SendByteArray[3] = offset_1;       //偏移量低字节
                SendByteArray[4] = offset_0;       //偏移量低字节

                SendByteArray[5] = count;       //读出字节数量
                //发送、接收、显示

                sci.SCISendFrameData(ref SendByteArray);

                //sci.SCISendData(ref SendByteArray);
                Thread.Sleep(500);
                if (sci.SCIReceiveData(ref recvData))
                {
                    //MessageBox.Show( Encoding.Default.GetString(recvData));
                    string str = null;
                    this.Txt_recv2.Text = Encoding.Default.GetString(recvData);
                    for (int i = 0; i < recvData.Length; i++)
                    {
                        str += recvData[i].ToString("X2");
                        str += "-";
                    }
                    this.Txt_recv1.Text = str;    //16进制字符串
                }
            }
            catch
            {
                this.Txt_recv1.Text = "终端UE Flash读取操作失败！";
            }
        }


        //---------------------------Flash写入操作按钮点击事件----------------------------
        private void btnPnFlashWrite_Click(object sender, EventArgs e)
        {

            byte sector;        //扇区号
            int offset;         //偏移量
            byte n;             //读取字节数
            int i;
            byte len;
            // 2. 临时变量赋值tbOffset2
 
            sector = Convert.ToByte(tbSector2.Text);  // 将TextBox中的Text转换为Byte类型
            if (sector < 30)
            {
                MessageBox.Show("请输入正确扇区号！");
                return;
            }
            offset = Convert.ToInt32(tbOffset2.Text);   // 将TextBox中的Text转换为Byte类型
            if (offset%4!=0)
            {
                MessageBox.Show("请保证偏移量为4的倍数！");
                return;
            }
        
        }
        //---------------------------Flash擦除操作按钮点击事件----------------------------
        private void btnPnFlashErase_Click(object sender, EventArgs e)
        {
            if (Convert.ToInt16(tbSector3.Text) < 30)
            {
                MessageBox.Show("请输入正确扇区号！");
                return;
            }
            
            
            // 1. 临时变量声明
            byte sector;                         // 扇区号
            

            // 2. 临时变量赋值
            sector = Convert.ToByte(tbSector3.Text);  // 将TextBox中的Text转换为Byte类型

            for (byte ii = 0; ii < data_num; ii++)
            {
                byte[] SendByteArray = new byte[2];  //定义发送缓冲区
                this.Txt_recv1.Text = "";
                this.Txt_recv2.Text = "";
                this.Txt_recv1.Refresh();
                this.Txt_recv2.Refresh();

                this.tb_statue.Text = "运行状态：" + "单击“终端UE Flash 擦除测试”按钮...";
                this.tb_statue.Refresh();

                try
                {

                    SendByteArray[0] = (byte)'e';      //帧尾
                    SendByteArray[1] = (byte)(sector + ii);         //扇区号

                    //发送、接收、显示
                    sci.SCISendFrameData(ref SendByteArray);
                    Thread.Sleep(500);
                    if (sci.SCIReceiveData(ref recvData))
                    {
                        //MessageBox.Show(Encoding.Default.GetString(recvData));
                        string str = null;
                        this.Txt_recv2.Text = Encoding.Default.GetString(recvData);
                        for (int i = 0; i < recvData.Length; i++)
                        {
                            str += recvData[i].ToString("X2");
                            str += "-";
                        }
                        this.Txt_recv1.Text = str;    //16进制字符串
                    }
                }
                catch
                {
                    this.Txt_recv1.Text = "终端UE Flash读取写入失败,检查UART_User串口连接是否成功！";
                }
            }
        }
      

        //------------------------------发送 接收并解析--------------------------------------
        private void sendRecv(byte[] SendByteArray,int cnt,int time)

        {

        }



        

        //---------------------------单击“清空显示框”按钮-------------------------------
        private void btnClear1_Click(object sender, EventArgs e)
        {
            this.tb_statue.Text = "运行状态：" + "单击“清空显示框”按钮。";
            this.tb_statue.Refresh();
           
            this.Txt_recv1.Text = "";
            this.Txt_recv2.Text = "";
        }

        private void rBtnTargetComm_CheckedChanged(object sender, EventArgs e)
        {
           

            this.tb_statue.Text = "运行状态：" + "终端UE Flash测试";
            this.tb_statue.Refresh();


        }


        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            throw new System.NotImplementedException();
        }
        private void bindListCiew()
        {
            this.listView1.Columns.Add("StuID");
         //   this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.Columns.Add("Name");
        //    this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.Columns.Add("Grade");
            this.listView1.View = System.Windows.Forms.View.Details;

        }
        private void Form1_Load(object sender, EventArgs e)
        {
            bindListCiew();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MySqlConnection myconn = null;
            MySqlCommand mycom = null;
            MySqlDataAdapter myrec = null;
            myconn = new MySqlConnection("Host =localhost;Database=student;Username=root;Password=nch666666");
            myconn.Open();
            mycom = myconn.CreateCommand();
            mycom.CommandText = "SELECT *FROM student1";
            MySqlDataAdapter adap = new MySqlDataAdapter(mycom);
            DataSet ds = new DataSet();
            adap.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0].DefaultView;
            string sql = string.Format("select * from student1 ");
            mycom.CommandText = sql;
            mycom.CommandType = CommandType.Text;
            MySqlDataReader sdr = mycom.ExecuteReader();
            int i = 0;
            bindListCiew();
            
            
            byte sector;        //扇区号
            int offset;         //偏移量
            byte xx;
            sector = Convert.ToByte(tbSector2.Text);
            offset = Convert.ToInt32(tbOffset2.Text);
            xx=Convert.ToByte(tbWriteData1.Text.Trim().Length);
            byte ssector = sector;
            while (sdr.Read())
            {
                data_num++;   //定义一个全局变量
                listView1.Items.Add(sdr[0].ToString());
                listView1.Items[i].SubItems.Add(sdr[1].ToString());
                listView1.Items[i].SubItems.Add(sdr[2].ToString());



                string s="";
                s = "StuID:"+sdr[0].ToString();
                s = s + "  Name:" + sdr[1].ToString();
                s = s + "  Grade:" + sdr[2].ToString();

                byte n;             //读取字节数
                int ii;
                byte len;
                
                
                
                sector = (byte)(ssector + i);
                
                n = (byte)s.Length;

                for (int iii = n; iii < 30; iii++) s = s + " ";
                
                n = 30;
                
                byte[] writeDataArray = System.Text.Encoding.Default.GetBytes(s); //String转化为Byte[]

                byte[] SendByteArray = new byte[n+5];

                this.Txt_recv1.Text = "";
                this.Txt_recv2.Text = "";
                this.Txt_recv1.Refresh();
                this.Txt_recv2.Refresh();
                
                
                
                this.tb_statue.Text = i.ToString()+" "+sector.ToString()+" "+s;
             //   this.tb_statue.Text = "运行状态：" + "单击“终端UE Flash 写测试”按钮...";
                this.tb_statue.Refresh();
                try
                {

                    SendByteArray[0] = (byte) 'w';
                    SendByteArray[1] = sector; //第几页
                    SendByteArray[2] = (byte) (offset / 256); //偏移量高字节
                    SendByteArray[3] = (byte) (offset % 256); //偏移量低字节
                    SendByteArray[4] = n; //写入字节数
                    for (ii = 5; ii < 5 + n; ii++)
                    {
                        SendByteArray[ii] = writeDataArray[ii - 5];
                    }


                    //发送、接收、显示
                    //sci.SCISendData(ref SendByteArray);
                    sci.SCISendFrameData(ref SendByteArray);

                    Thread.Sleep(500);
                    if (sci.SCIReceiveData(ref recvData))
                    {
                        string str = null;
                        this.Txt_recv2.Text += Encoding.Default.GetString(recvData, 0, recvData.Length); //byte数组

                        for (int j = 0; j < recvData.Length; j++)
                        {
                            str += recvData[j].ToString("X2"); //字符
                            str += "-";
                        }

                        this.Txt_recv1.Text = str; //16进制字符串 
                    }
                }
                catch
                {
                    this.Txt_recv1.Text = "终端UE Flash读取写入失败,检查UART_User串口连接是否成功！";
                }

                i++;
            }
            myconn.Close();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            throw new System.NotImplementedException();
        }

        private void tbWriteData1_TextChanged(object sender, EventArgs e)
        {
            throw new System.NotImplementedException();
        }

        private void Txt_recv2_TextChanged(object sender, EventArgs e)
        {
            throw new System.NotImplementedException();
        }

        private void tb_statue_TextChanged(object sender, EventArgs e)
        {
            throw new System.NotImplementedException();
        }

        private void groupBox9_Enter(object sender, EventArgs e)
        {
            throw new System.NotImplementedException();
        }
    }
}
