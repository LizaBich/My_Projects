﻿using System.Windows.Forms;

namespace ImageViwer
{
    public interface IMessageService
    {
        void ShowMessage(string message);
        void ShowExclamation(string message);
        void ShowError(string message);
    }

    public class MessageService : IMessageService
    {
        public void ShowError(string message)
        {
            MessageBox.Show(message, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public void ShowExclamation(string message)
        {
            MessageBox.Show(message, "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }

        public void ShowMessage(string message)
        {
            MessageBox.Show(message, "Сообщение", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
