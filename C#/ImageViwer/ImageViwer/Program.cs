using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using ImageViewer.BL;

namespace ImageViwer
{
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            MainForm form = new MainForm();
            MessageService message = new MessageService();
            ImageManager manager = new ImageManager();
            MainPresenter presenter = new MainPresenter(form, manager, message);

            Application.Run(form);
        }
    }
}
