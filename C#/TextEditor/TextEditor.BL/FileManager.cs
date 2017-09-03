using System.IO;
using System.Text;

namespace TextEditor.BL
{
    public interface IFileManager
    {
        string GetContent(string filePath);
        string GetContent(string filePath, Encoding encoding);
        void SaveContent(string content, string filePath, Encoding encoding);
        void SaveContent(string content, string filePath);
        bool IsExist(string filePath);
        int GetSymbolCount(string content);
    }

    public class FileManager: IFileManager
    {
        private readonly Encoding _defaultEncoding = Encoding.GetEncoding(1251);   // стандартная кодировка в Windows

        public string GetContent(string filePath)
        {
            return GetContent(filePath, _defaultEncoding);
        }

        public string GetContent(string filePath, Encoding encoding)
        {
            return File.ReadAllText(filePath, encoding);
        }

        public void SaveContent(string content, string filePath, Encoding encoding)
        {
            File.WriteAllText(filePath, content, encoding);
        }

        public void SaveContent(string content, string filePath)
        {
            SaveContent(content, filePath, _defaultEncoding);
        }

        public bool IsExist(string filePath)
        {
            return File.Exists(filePath);
        }

        public int GetSymbolCount(string content)
        {
            return content.Length;
        }
    }
}
