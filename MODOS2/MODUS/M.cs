using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.Reflection;
using System.Reflection.Emit;

namespace Pin_13_on_off
{
    public partial class Form1 : Form
    {
        public static string Connection;
        public static bool Connected=false;
        
        public Form1()
        {
            InitializeComponent();
            foreach(string port in SerialPort.GetPortNames())
            {
                try
                {
                    serialPort1.Close();
                    serialPort1.PortName = port;
                    serialPort1.Open();
                    if (serialPort1.IsOpen)
                    {
                        serialPort1.Write("C");
                        Connection = serialPort1.ReadChar().ToString();
                    }
                    if (Connection == "67")
                    {
                        serialPort1.Close();
                        serialPort1.PortName = port;
                        serialPort1.Open();
                        MessageBox.Show("Connected to Arduino", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        Connected = true;
                        break;
                    }
                    
                }
                catch (System.UnauthorizedAccessException) { MessageBox.Show(port.ToString() + " is Busy"); }
                catch (System.TimeoutException) { continue; }
                catch (System.IO.IOException e)
                {
                    MessageBox.Show(e.ToString());
                    serialPort1.Close();
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Write("A");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Write("B");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            foreach (string port in SerialPort.GetPortNames())
            {
                try
                {
                    serialPort1.Close();
                    serialPort1.PortName = port;
                    serialPort1.Open();
                    if (serialPort1.IsOpen)
                    {
                        serialPort1.Write("C");
                        Connection = serialPort1.ReadChar().ToString();
                    }
                    if (Connection == "67")
                    {
                        serialPort1.Close();
                        serialPort1.PortName = port;
                        serialPort1.Open();
                        MessageBox.Show("Connected to Arduino", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        Connected = true;
                        break;
                    }
                }
                catch (System.TimeoutException) { continue; }
                catch (System.IO.IOException) { continue; }
                catch (System.UnauthorizedAccessException) { MessageBox.Show("Port is in use", "Unauthorized Access", MessageBoxButtons.OK, MessageBoxIcon.Information); }
                {
                    serialPort1.Close();
                    MessageBox.Show("Arduino is not connected", "Connection Fail", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                if (Connected == false)
                {
                    MessageBox.Show("Arduino is not connected", "Connection Fail", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }

            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.Close();
                serialPort1.Open();
                if (serialPort1.IsOpen)
                {
                    serialPort1.Write("D");
                    Thread.Sleep(50);
                    MessageBox.Show(serialPort1.ReadLine().ToString());
                }
            }
            catch (System.TimeoutException) { MessageBox.Show("TimedOut"); }
            catch (System.IO.IOException)
            {
                serialPort1.Close();
                MessageBox.Show("Arduino is not connected", "Connection Fail", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }


        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
           

        }
    }
}
