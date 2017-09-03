using System;
using TextEditor.BL;

namespace TextEditor
{
    public class MainPresenter
    {
        private readonly IMainForm _view;
        private readonly IFileManager _manager;
        private readonly IMessageService _messageService;
        private string _currentFilePath;

        public MainPresenter(IMainForm view, IFileManager manager, IMessageService service)
        {
            _view = view;
            _manager = manager;
            _messageService = service;

            _view.SetSymbolCount(0);
            _view.ContentChanged += new EventHandler(_view_ContentChanged);
            _view.FileOpenClick += new EventHandler(_view_FileOpen);
            _view.FileSaveClick += new EventHandler(_view_FileSave);
        }

        private void _view_FileSave(object sender, EventArgs e)
        {
            try
            {
                _manager.SaveContent(_view.Content, _currentFilePath);
                _messageService.ShowMessage("Файл успешно сохранён.");
            }
            catch (Exception ex)
            {
                _messageService.ShowError(ex.Message);
            }
        }

        private void _view_FileOpen(object sender, EventArgs e)
        {
            try
            {
                if (!_manager.IsExist(_view.FilePath))
                {
                    _messageService.ShowExclamation("Выбранный файл не существует");
                    return;
                }

                _currentFilePath = _view.FilePath;

                string content = _manager.GetContent(_view.FilePath);

                _view.Content = content;
                _view.SetSymbolCount(_manager.GetSymbolCount(content));
            }
            catch (Exception ex)
            {
                _messageService.ShowError(ex.Message);
            }
        }

        private void _view_ContentChanged(object sender, EventArgs e)
        {
            _view.SetSymbolCount(_manager.GetSymbolCount(_view.Content));
        }
    }
}
