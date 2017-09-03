using System.Drawing;
using System.IO;

namespace ImageViewer.BL
{
    public interface IImageManager
    {
        Image GetContent(string filePath);
        bool IsExist(string filePath);
    }

    public class ImageManager : IImageManager
    {
        public Image GetContent(string filePath) => Image.FromFile(filePath);

        public bool IsExist(string filePath) => File.Exists(filePath);
    }
}
