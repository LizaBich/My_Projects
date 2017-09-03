using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageViwer
{
    public interface IMainForm
    {
        string FilePath { get; }
        Image Content { get; set;}

        event EventHandler ImageOpenClick;
    }

    public partial class MainForm : Form, IMainForm
    {
        public event EventHandler ImageOpenClick;

        public MainForm()
        {
            InitializeComponent();
            btnOpen.Click += new EventHandler(btnOpen_Click);
            btnSelect.Click += new EventHandler(btnSelect_Click);
        }

        public string FilePath
        {
            get
            {
                return scFilePath.Text;
            }
        }

        public Image Content
        {
            get
            {
                return viewImage.Image;
            }

            set
            {
                viewImage.Image = value;
            }
        }
        
        private void btnSelect_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Изображения| *.jpeg; *.jpg; *.png|Все файлы|*.*";

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                scFilePath.Text = dlg.FileName;

                ImageOpenClick?.Invoke(this, EventArgs.Empty);
            }
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            ImageOpenClick?.Invoke(this, EventArgs.Empty);
        }
    }
}
