using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ImageViewer.BL;

namespace ImageViwer
{
    public class MainPresenter
    {
        private readonly IMainForm _view;
        private readonly IImageManager _manager;
        private readonly IMessageService _message;
        private string _currentPath;

        private void _view_ImageOpen(object sender, EventArgs e)
        {
            try
            {
                if (_view.FilePath == String.Empty)
                {
                    _message.ShowExclamation("Укажите путь к файлу!");
                    return;
                }
                if (!_manager.IsExist(_view.FilePath))
                {
                    _message.ShowExclamation("Выбранный файл не найден.");
                    return;
                }

                _currentPath = _view.FilePath;
                _view.Content = _manager.GetContent(_view.FilePath);
            }
            catch(Exception ex)
            {
                _message.ShowError(ex.Message);
            }
        }

        public MainPresenter(IMainForm view, IImageManager manager, IMessageService message)
        {
            _view = view;
            _manager = manager;
            _message = message;

            _view.ImageOpenClick += new EventHandler(_view_ImageOpen);
        }
    }
}
