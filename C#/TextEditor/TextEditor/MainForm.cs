using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TextEditor
{
    public interface IMainForm
    {
        string FilePath { get; }
        string Content { get; set; }
        void SetSymbolCount(int count);

        event EventHandler FileOpenClick;
        event EventHandler FileSaveClick;
        event EventHandler ContentChanged;
    }

    public partial class MainForm : Form, IMainForm
    {
        public MainForm()
        {
            InitializeComponent();
            btnOpen.Click += new EventHandler(btnOpenFile_Click);
            btnSelect.Click += new EventHandler(btnSelect_Click);
            textScreen.TextChanged += new EventHandler(textScreen_TextChanged);
            btnSave.Click += new EventHandler(btnSave_Click);
            numericFont.ValueChanged += new EventHandler(numericFont_ValueChanged);
            textScreen.Font = new Font("Calibri", 14.0f);
        }
        
        #region probros
        private void textScreen_TextChanged(object sender, EventArgs e)
        {
            ContentChanged?.Invoke(this, EventArgs.Empty);
        }
        private void btnSave_Click(object sender, EventArgs e)
        {
            FileSaveClick?.Invoke(this, EventArgs.Empty);
        }

        private void btnOpenFile_Click(object sender, EventArgs e)
        {
            FileOpenClick?.Invoke(this, EventArgs.Empty);
        }
        #endregion

        #region IMainForm
        public string FilePath
        {
            get { return ScFilePath.Text; }
        }

        public string Content
        {
            get { return textScreen.Text; }
            set { textScreen.Text = value; }
        }

        public void SetSymbolCount(int count)
        {
            countStatus.Text = Convert.ToString(count);
        }

        public event EventHandler FileOpenClick;
        public event EventHandler FileSaveClick;
        public event EventHandler ContentChanged;
        #endregion

        private void btnSelect_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Текстовые файлы| *.txt|Все файлы|*.*";

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                ScFilePath.Text = dlg.FileName;

                FileOpenClick?.Invoke(this, EventArgs.Empty);
            }
        }

        private void numericFont_ValueChanged(object sender, EventArgs e)
        {
            textScreen.Font = new Font("Calibri", (float)numericFont.Value);
        }
    }
}
