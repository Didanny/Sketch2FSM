using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Sketch2FSM_UI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        public void ImagePanel_Drop(object sender, DragEventArgs e)
        {

            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                // Can have more than one file
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);

                // Setting label content to full path of file
                //TestLabel.Content = files[0].ToString();

                Image i = new Image();
                BitmapImage src = new BitmapImage();
                src.BeginInit();
                src.UriSource = new Uri(files[0].ToString(), UriKind.Relative);
                src.CacheOption = BitmapCacheOption.OnLoad;
                src.EndInit();
                i.Source = src;
                i.Stretch = Stretch.Uniform;
                //int q = src.PixelHeight;        // Image loads here
                sp.Children.Add(i);
                ImagePanel.Height = 0;

                Canvas.Height = sp.Height;
                Canvas.Width = sp.Width;
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            TestBlock.Text = "Clicked";
            DrawCircle(0, 0, 0);
        }

        private void DrawCircle(double radius, double center_x, double center_y)
        {
            Ellipse e = new Ellipse();
            e.Height = 60;
            e.Width = 60;
            Canvas.Children.Add(e);
        }
    }
}
