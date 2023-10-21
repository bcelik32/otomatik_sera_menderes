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

namespace seriport
{
    public partial class Form1 : Form
    {
        string veri;
        int adet = 0;
        bool s_fandurum = false;
        bool so_fandurum = false;
        bool catiperde_durum = false;
        bool oto = false;
        bool sulama = false;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            foreach (string port in ports)
                comboBox1.Items.Add(port);

            serialPort1.DataReceived += new SerialDataReceivedEventHandler(SerialPort1_DataReceived);
        }
        private void SerialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            veri = serialPort1.ReadLine();
            this.Invoke(new EventHandler(displayData_event));
        }

        private void displayData_event(object sender, EventArgs e)
        {

        }
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.PortName = comboBox1.SelectedItem.ToString();
            //serialPort1.Open();
        }
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen) serialPort1.Close();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                if (comboBox1.Text == "        Seri Port Seç")
                {
                    MessageBox.Show("Lütfen port seçiniz", "Uyarı");

                }
                else
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.BaudRate = 9600;
                    serialPort1.Open();
                    durum_text.Text = "Durum: Bağlı";
                    MessageBox.Show("Seri Port Bağlandı", "Başarılı");
                    button5.Enabled = true;
                    button2.Enabled = true;
                    button1.Enabled = false;


                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Hata");
            }

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            durum_text.Text = "Durum: Bağlı Değil";
            button1.Enabled = true;
            button3.Enabled = false;
            button7.Enabled = false;
            button4.Enabled = false;
            button6.Enabled = false;
            button2.Enabled = false;
            trackBar1.Enabled = false;
            button5.Enabled = false;
            so_fandurum = false;
            s_fandurum = false;
            catiperde_durum = false;
            button4.BackColor = Color.Red;
            button3.BackColor = Color.Red;
            button6.BackColor = Color.Red;
            MessageBox.Show("Bağlantı Kesildi", "Başarılı");

        }

        private void button4_Click(object sender, EventArgs e)
        {

            if (so_fandurum == false)
            {
                button4.BackColor = Color.Lime;
                so_fandurum = true;
                button3.Enabled = false;
                button6.Enabled = false;
                serialPort1.Write("e");

            }
            else
            {
                button4.BackColor = Color.Red;
                so_fandurum = false;
                button3.Enabled = true;
                button6.Enabled = true;
                serialPort1.Write("r");

            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (s_fandurum == false)
            {
                button3.BackColor = Color.Lime;
                s_fandurum = true;
                button4.Enabled = false;
                button6.Enabled = false;
                serialPort1.Write("t");
            }
            else
            {
                button3.BackColor = Color.Red;
                s_fandurum = false;
                button4.Enabled = true;
                button6.Enabled = true;
                serialPort1.Write("y");
            }

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button5_Click_1(object sender, EventArgs e)
        {
            if (oto == false)
            {
                oto = true;
                button5.Text = "Otomatik Mod";
                button3.Enabled = false;
                button4.Enabled = false;
                button6.Enabled = false;
                trackBar1.Enabled = false;
                button8.Enabled = false;
                button7.Enabled = false;
                numericUpDown1.Enabled = false;
                so_fandurum = false;
                s_fandurum = false;
                catiperde_durum = false;
                button4.BackColor = Color.Red;
                button3.BackColor = Color.Red;
                serialPort1.Write("o");
            }
            else
            {
                button5.Text = "Manuel Mod";
                oto = false;
                button3.Enabled = true;
                button4.Enabled = true;
                button6.Enabled = true;
                button7.Enabled = true;
                trackBar1.Enabled = true;
                button8.Enabled = true;
                numericUpDown1.Enabled = true;
                serialPort1.Write("m");

            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (catiperde_durum == false)
            {
                button6.BackColor = Color.Lime;
                catiperde_durum = true;
                s_fandurum = false;
                so_fandurum = false;
                button3.Enabled = false;
                button4.Enabled = false;
                serialPort1.Write("w");
            }
            else
            {
                button6.BackColor = Color.Red;
                catiperde_durum = false;
                button3.Enabled = true;
                button4.Enabled = true;
                serialPort1.Write("q");
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            int sulamasuresi = (int)numericUpDown1.Value;
            sulama = true;
            progressBar1.Minimum = 0;
            progressBar1.Maximum = sulamasuresi;
            progressBar1.Value = 0;
            button2.Enabled = false;
            serialPort1.Write("u");
            for (int i = 0; i < sulamasuresi; i++)
            {
                progressBar1.Value = i + 1;
                Application.DoEvents();
                Thread.Sleep(1000);
                if (sulama == false)
                {
                    break;
                }
            }
            serialPort1.Write("p");
            progressBar1.Value = 0;
            button2.Enabled = true;
        }

        private void button5_MouseEnter(object sender, EventArgs e)
        {
            button5.ForeColor= Color.Red;
        }

        private void button5_MouseLeave(object sender, EventArgs e)
        {
            button5.ForeColor = Color.Black;

        }

        private void button7_Click(object sender, EventArgs e)
        {
            serialPort1.Write("p");
            progressBar1.Value = 0;
            sulama = false;
        }

        private void groupBox4_Enter(object sender, EventArgs e)
        {

        }

        private void groupBox3_Enter(object sender, EventArgs e)
        {

        }

        private void frame_kontrol_Enter(object sender, EventArgs e)
        {

        }
    }
}
