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
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace Sketch2FSM_UI
{
    //C:\Users\Danny\Desktop\AUB\EECE 437\OpenCVtest\OpenCVtest\C#\sketch2fsmlib\x64\Debug\sketch2fsmlib.dll

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void Start();

        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void LoadSketch(const char*, int);

        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void FindConnectedComponents();

        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void FindContainers();

        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void FindCircles();

        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void FindCharacters();

        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void FindArrows();

        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void ParseLabels();

        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void CreateStates();

        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void CreateTransitions();

        //[DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll",
        //CallingConvention = CallingConvention.Cdecl)]
        //public static extern void OutputFile();

        public string ImagePath;

        public MainWindow()
        {
            InitializeComponent();
            KeyDown += MainWindowKeyDown;
            DrawingSurface.MouseMove += DrawingSurfaceMouseMove;
            DrawingSurface.MouseDown += DrawingSurfaceMouseDown;
            DrawingSurface.MouseUp += DrawingSurfaceMouseUp;
            //_pen = new Pen(DrawingSurface);
            //DrawingSurface.Focus();
        }

        public int imageWidth;
        public int imageHeight;

        public List<IDrawable> components;
        public int selected = 0;

        double origin_x;
        double origin_y;
        double final_x;
        double final_y;

        int numNewStates = 0;

        public double Distance(double x1, double x2, double y1, double y2)
        {
            return Math.Sqrt(Math.Pow(x1 - x2, 2) + Math.Pow(y1 - y2, 2));
        }

        private void DrawingSurfaceMouseUp(object sender, MouseButtonEventArgs e)
        {
            BeginInvoke(new Action(() => {
                final_x = Mouse.GetPosition(DrawingSurface).X;// * ImageDimensions.Image.width / ImageDimensions.Panel.width;
                final_y = Mouse.GetPosition(DrawingSurface).Y;// * ImageDimensions.Image.height / ImageDimensions.Panel.width;
                double radius = Distance(origin_x, final_x, origin_y, final_y) / 2.0;

                Debug.WriteLine("Second point:" + final_x.ToString() + "," + final_y.ToString());
                Debug.WriteLine(StateRadio.IsChecked.ToString());
                Debug.WriteLine(ArrowRadio.IsChecked.ToString());

                if (StateRadio.IsChecked ?? false)
                {
                    numNewStates--;
                    components.Add(new State(numNewStates, "unknown", new Ellipse
                    {
                        StrokeThickness = 2,
                        Margin = new Thickness(Math.Min(origin_x, final_x), Math.Min(origin_y, final_y), 0, 0),
                        Height = (radius * 2),
                        Width = (radius * 2)
                    }));
                    Debug.WriteLine("Components=" + components.Count.ToString());
                }
                else if (ArrowRadio.IsChecked ?? false)
                {
                    numNewStates--;
                    components.Add(new Transition(0, 0, "unknown", new Line
                    {
                        StrokeThickness = 2,
                        X1 = origin_x,
                        X2 = final_x,
                        Y1 = origin_y,
                        Y2 = final_y
                    },
                    new Ellipse
                    {
                        StrokeThickness = 2,
                        Margin = new Thickness(final_x, final_y, 0, 0),
                        Height = 5,
                        Width = 5
                    }));
                    //selected = components.Count;
                    Debug.WriteLine("Components=" + components.Count.ToString());
                }
                //components = components.Distinct().ToList();
                Redraw();
            }));
        }

        // Workaround to stop mouseup event from being handled twice
        private void BeginInvoke(Action action)
        {
            action.Invoke();
        }

        private void DrawingSurfaceMouseDown(object sender, MouseButtonEventArgs e)
        {
            //if (LineRadioButton.IsChecked == true)
            // _dr = new MyPath(Mouse.GetPosition(DrawingSurface));
            // else if (CircleRadioButton.IsChecked == true)
            //try
            //{
            //    _dr = new MyCircle(Mouse.GetPosition(DrawingSurface));
            //    _pen.Down(_dr);
            //}
            //catch
            //{
            //    return;
            //}
            origin_x = Mouse.GetPosition(DrawingSurface).X;// * ImageDimensions.Image.width / ImageDimensions.Panel.width;
            origin_y = Mouse.GetPosition(DrawingSurface).Y;// * ImageDimensions.Image.height / ImageDimensions.Panel.width;

            Debug.WriteLine("First point:" + origin_x.ToString() + "," + origin_y.ToString());
        }

        private void DrawingSurfaceMouseMove(object sender, MouseEventArgs e)
        {
            //if (_dr != null)
            //    _pen.Draw(_dr, Mouse.GetPosition(DrawingSurface));
        }

        private void MainWindowKeyDown(object sender, KeyEventArgs e)
        {
            //if (e.Key == Key.Enter)
            //    DrawingSurface.Children.Clear();
        }



        public void ImagePanel_Drop(object sender, DragEventArgs e)
        {

            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                // Can have more than one file
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);

                // Setting label content to full path of file
                //TestLabel.Content = files[0].ToString();

                ImagePath = files[0].ToString();

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
            }
        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {
            if (ImagePath.Length < 1) return;

            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.CreateNoWindow = false;
            startInfo.UseShellExecute = false;
            startInfo.FileName = "C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\x64\\Debug\\OpenCVtest.exe";
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.Arguments = "\"" + ImagePath +"\" >> ./a.txt";

            using (Process exeProcess = Process.Start(startInfo))
            {
                exeProcess.WaitForExit();
            }

            // Read from the output file
            string line;
            string[] splitted;
            System.IO.StreamReader file = new System.IO.StreamReader(@"./output.txt");

            line = file.ReadLine();
            splitted = line.Split(',');

            imageWidth = Int32.Parse(splitted[0]);
            imageHeight = Int32.Parse(splitted[1]);

            ImageDimensions.Image.width = Int32.Parse(splitted[0]);
            ImageDimensions.Image.height = Int32.Parse(splitted[1]);
            ImageDimensions.Panel.width = (int)((0.75 * Width) - 100);
            ImageDimensions.Panel.height = (int)(((0.75 * Width) - 100) / 1.7);

            //Debug.WriteLine(ImageDimensions.Image.width);
            //Debug.WriteLine(ImageDimensions.Image.height);
            //Debug.WriteLine(ImageDimensions.Panel.width);
            //Debug.WriteLine(ImageDimensions.Panel.height);


            components = new List<IDrawable>();

            while ((line = file.ReadLine()) != null)
            {
                splitted = line.Split(',');
                if (splitted[0].Equals("T"))
                {
                    components.Add(new Transition(Int32.Parse(splitted[1]), Int32.Parse(splitted[2]), splitted[3], Double.Parse(splitted[4]), Double.Parse(splitted[5]), Double.Parse(splitted[6]), Double.Parse(splitted[7])));
                }
                else
                {
                    State state = new State(Int32.Parse(splitted[2]), splitted[1], Double.Parse(splitted[3]), Double.Parse(splitted[4]), Double.Parse(splitted[5]));
                    if (Convert.ToBoolean(Int32.Parse(splitted[6])))
                    {
                        state.SetAccept();
                    }
                    components.Add(state);
                }
            }

            // Drawing the existing components
            for (int i = 0; i < components.Count; i++)
            {
                if (i == selected) components.ElementAt(i).Draw(DrawingSurface, Brushes.Red);
                else components.ElementAt(i).Draw(DrawingSurface, Brushes.Black);
            }

            // Initalize the editting panel
            //if (components.ElementAt(selected) is State)
            //{
            //    State state = (State)components.ElementAt(selected);
            //    Label.Text = state.name;
            //}
            //else if (components.ElementAt(selected) is Transition)
            //{
            //    Transition trans = (Transition)components.ElementAt(selected);
            //    Label.Text = trans.label;
            //}
            InitStatePanel();
            DisplayComponentInfo();

            Show();
        }

        public void Redraw()
        {
            ImageDimensions.Panel.width = (int)((0.75 * Width) - 100);
            ImageDimensions.Panel.height = (int)(((0.75 * Width) - 100) / 1.7);
            DrawingSurface.Children.Clear();
            if (components == null) return;
            for (int i = 0; i < components.Count; i++)
            {
                if (i == selected) components.ElementAt(i).Draw(DrawingSurface, Brushes.Red);
                else components.ElementAt(i).Draw(DrawingSurface, Brushes.Black);
            }
            Show();
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            Redraw();
        }

        private void InitStatePanel()
        {
            ArrowPanel.Visibility = Visibility.Collapsed;
            StatePanel.Visibility = Visibility.Visible;
        }

        private void InitArrowPanel()
        {
            StatePanel.Visibility = Visibility.Collapsed;
            ArrowPanel.Visibility = Visibility.Visible;
        }

        private void DisplayComponentInfo()
        {
            // Display the information of the next component
            if (components.ElementAt(selected) is State)
            {
                // Initialize Panel
                InitStatePanel();

                State state = (State)components.ElementAt(selected);
                Label.Text = state.name;
                IsAccept.IsChecked = state.is_accept;
                Redraw();
            }
            else if (components.ElementAt(selected) is Transition)
            {
                //Initialize Panel
                InitArrowPanel();
       
                Transition trans = (Transition)components.ElementAt(selected);
                Label.Text = trans.label;
                From.Text = FindStateName(trans.source);
                To.Text = FindStateName(trans.destination);
                Redraw();
            }
        }

        private string FindStateName(int label)
        {
            foreach (IDrawable d in components)
            {
                if (d is State)
                {
                    State s = (State)d;
                    if (label == s.label)
                    {
                        return s.name;
                    }
                }
            }
            return "unknown";
        }

        private int FindStateLabel(string name)
        {
            foreach (IDrawable d in components)
            {
                if (d is State)
                {
                    State s = (State)d;
                    if (name == s.name)
                    {
                        return s.label;
                    }
                }
            }
            return 0;
        }

        private void SaveChanges()
        {
            // Save changes made previously
            if (components.ElementAt(selected) is State)
            {
                State state = (State)components.ElementAt(selected);
                state.name = Label.Text;
                state.is_accept = IsAccept.IsChecked ?? false;
            }
            else if (components.ElementAt(selected) is Transition)
            {
                Transition trans = (Transition)components.ElementAt(selected);
                trans.label = Label.Text;
                trans.source = FindStateLabel(From.Text);
                trans.destination = FindStateLabel(To.Text);
            }
        }

        private void Left_Click(object sender, RoutedEventArgs e)
        {
            // Save changes made previously
            SaveChanges();

            // Decrement selected index
            selected -= 1;
            if (selected < 0) selected = components.Count;
            if (selected < 0) return;

            // Display the information of the next component
            DisplayComponentInfo();
        }

        private void Right_Click(object sender, RoutedEventArgs e)
        {
            // Save changes made previously
            SaveChanges();

            // Increment the selected index
            selected = (selected + 1) % components.Count;
            if (selected < 0) return;

            // Display the information of the next component
            DisplayComponentInfo();
        }

        private void Flip_Click(object sender, RoutedEventArgs e)
        {
            Transition trans = (Transition)components.ElementAt(selected);
            double x = trans.destination_x;
            double y = trans.destination_y;
            int temp = trans.destination;

            trans.destination_x = trans.source_x;
            trans.destination_y = trans.source_y;
            trans.destination = trans.source;

            trans.source_x = x;
            trans.source_y = y;
            trans.source = temp;

            string to = To.Text;
            To.Text = From.Text;
            From.Text = to;

            if (trans.Head.Margin.Top == trans.Arrow.Y1)
            {
                trans.Head.Margin = new Thickness(trans.Arrow.X2, trans.Arrow.Y2, 0, 0);
            }
            else
            {
                trans.Head.Margin = new Thickness(trans.Arrow.X1, trans.Arrow.Y1, 0, 0);
            }

            Redraw();
        }

        private void Delete_Click(object sender, RoutedEventArgs e)
        {
            if (components.Count != 0)
            {
                components.RemoveAt(selected);
                return;
            }

            selected = 0;
            Redraw();

            if (components.ElementAt(selected) is State)
            {
                InitStatePanel();
            }
            else
            {
                InitArrowPanel();
            }
            DisplayComponentInfo();
        }
    }
}
