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
using System.IO;
using System.Text.RegularExpressions;

namespace Sketch2FSM_UI
{
    //C:\Users\Danny\Desktop\AUB\EECE 437\OpenCVtest\OpenCVtest\C#\sketch2fsmlib\x64\Debug\sketch2fsmlib.dll
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


        public static string FilePath = "C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\x64\\Debug\\OpenCVtest.exe";
        public string ImagePath;

        public MainWindow()
        {
            InitializeComponent();
        }

        // List of components ad selected index
        public List<IDrawable> components;
        public int selected = 0;

        // The mouse click coords
        double origin_x;
        double origin_y;
        double final_x;
        double final_y;

        // Used to give labels to newly added states, negative labels not to conflict with OpenCV labels
        int numNewStates = 0;

        // Euclidean distance between 2 points
        public double Distance(double x1, double x2, double y1, double y2)
        {
            return Math.Sqrt(Math.Pow(x1 - x2, 2) + Math.Pow(y1 - y2, 2));
        }

        // Draw the new component and add it to the components List
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
                    Debug.WriteLine("Components=" + components.Count.ToString());
                }
                Redraw();
            }));
        }

        // Workaround to stop mouseup event from being handled twice
        private void BeginInvoke(Action action)
        {
            action.Invoke();
        }

        // Store the mouse position of where the drag started
        private void DrawingSurfaceMouseDown(object sender, MouseButtonEventArgs e)
        {
            origin_x = Mouse.GetPosition(DrawingSurface).X;// * ImageDimensions.Image.width / ImageDimensions.Panel.width;
            origin_y = Mouse.GetPosition(DrawingSurface).Y;// * ImageDimensions.Image.height / ImageDimensions.Panel.width;
        }

        // Get the path of the image that was dropped and show it
        public void ImagePanel_Drop(object sender, DragEventArgs e)
        {

            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);

                // Store the path of the image
                ImagePath = files[0].ToString();

                // Show the image dropped
                Image i = new Image();
                BitmapImage src = new BitmapImage();
                src.BeginInit();
                src.UriSource = new Uri(files[0].ToString(), UriKind.Relative);
                src.CacheOption = BitmapCacheOption.OnLoad;
                src.EndInit();
                i.Source = src;
                i.Stretch = Stretch.Uniform;
                sp.Children.Add(i);
                ImagePanel.Height = 0;
            }
        }

        // Read output file and initialize the components list
        private void Start_Click(object sender, RoutedEventArgs e)
        {
            if (ImagePath.Length < 1) return;

            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.CreateNoWindow = false;
            startInfo.UseShellExecute = false;
            startInfo.FileName = FilePath;
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.Arguments = "\"" + ImagePath +"\"";

            using (Process exeProcess = Process.Start(startInfo))
            {
                exeProcess.WaitForExit();
            }

            // Read from the output file
            string line;
            string[] splitted;
            System.IO.StreamReader file = new System.IO.StreamReader(@"./output.txt");

            // Split the first line, the image dimensions
            line = file.ReadLine();
            splitted = line.Split(',');

            // Store the image dimesnions
            ImageDimensions.Image.width = Int32.Parse(splitted[0]);
            ImageDimensions.Image.height = Int32.Parse(splitted[1]);
            ImageDimensions.Panel.width = (int)((0.75 * Width) - 100);
            ImageDimensions.Panel.height = (int)(((0.75 * Width) - 100) / 1.7);

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

            InitStatePanel();
            DisplayComponentInfo();

            Show();

            Start.Visibility = Visibility.Collapsed;
            Done.Visibility = Visibility.Visible;
        }

        // Redraw the components, color red if selected
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

        // Initializes the state panel
        private void InitStatePanel()
        {
            ArrowPanel.Visibility = Visibility.Collapsed;
            StatePanel.Visibility = Visibility.Visible;
        }

        // Initializes the arrow panel
        private void InitArrowPanel()
        {
            StatePanel.Visibility = Visibility.Collapsed;
            ArrowPanel.Visibility = Visibility.Visible;
        }

        // Displays the current selected component's info in the Editting Panel
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

        // Finds the name of a state whose label is label
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

        // For a given string, finds the label of the state whose name is name
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

        // Saves the changes the user made
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

        // Buggy for some reason, ommitted for now
        private void Left_Click(object sender, RoutedEventArgs e)
        {
            //// Save changes made previously
            //SaveChanges();

            //// Decrement selected index
            //selected -= 1;
            //if (selected < 0) selected = components.Count;
            //if (selected < 0) return;

            //// Display the information of the next component
            //DisplayComponentInfo();
        }

        // Rotate through the components
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

        // Flips the direction of the arrow selected
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

        // Deletes the selected component
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

        // Cleans up the state names according to VHDL syntax
        private string CleanUpName(string name)
        {
            name = name.ToUpper();
            name = Regex.Replace(name, @"\s+", "");
            name = "s" + name;
            return name;
        }

        // Takes all the changes made by the user and outputs the VHDL file
        private void Done_Click(object sender, RoutedEventArgs e)
        {
            SaveChanges();

            List<State> states = new List<State>();
            List<Transition> transitions = new List<Transition>();
            Dictionary<int, string> label2number = new Dictionary<int, string>();

            foreach (IDrawable drawable in components)
            {
                if (drawable is State)
                {
                    State s = (State)drawable;
                    s.name = CleanUpName(s.name);
                    states.Add(s);
                }
                else if (drawable is Transition)
                {
                    transitions.Add((Transition)drawable);
                }
            }

            int size = (int)Math.Ceiling(Math.Sqrt(states.Count));
            for (int i = 0; i < states.Count; i++)
            {
                label2number[states.ElementAt(i).label] = Convert.ToString(i, 2).PadLeft(size, '0');
            }

            using (StreamWriter OutVHDL = new StreamWriter("./FSM.vhd"))
            {
                OutVHDL.WriteLine("library ieee;");
                OutVHDL.WriteLine("use ieee.std_logic_1164.all;");
                OutVHDL.WriteLine("use ieee.numeric_std.all;");
                OutVHDL.WriteLine();
                OutVHDL.WriteLine("entity FSM is");
                OutVHDL.WriteLine("Port(\tclk : in std_logic;");
                OutVHDL.WriteLine("\treset : in std_logic;");
                OutVHDL.WriteLine("\tinput : in std_logic;");
                OutVHDL.WriteLine("\tstate_out : std_logic_vector (" + (size - 1).ToString() + " downto 0));");
                OutVHDL.WriteLine("end FSM;");
                OutVHDL.WriteLine();
                OutVHDL.WriteLine("architecture Behavioral of FSM is");
                OutVHDL.WriteLine();
                OutVHDL.Write("type state is (");
                for (int i = 0; i < states.Count; i++)
                {
                    OutVHDL.Write(states.ElementAt(i).name);
                    if (i != states.Count - 1)
                    {
                        OutVHDL.Write(",");
                    }
                }
                OutVHDL.WriteLine(");");
                OutVHDL.WriteLine("signal current_state, next_state : state;");
                OutVHDL.WriteLine();
                OutVHDL.WriteLine("begin");
                OutVHDL.WriteLine("seq : process (clk, reset)");
                OutVHDL.WriteLine("begin");
                OutVHDL.WriteLine();
                OutVHDL.Write("if (reset = '1') then current_state <= ");
                foreach (State state in states)
                {
                    if (state.is_accept)
                    {
                        OutVHDL.Write(state.name + ";");
                        break;
                    }
                }
                OutVHDL.WriteLine();
                OutVHDL.WriteLine("elsif (clk' event and clk = '1') then current_state <= next_state;");
                OutVHDL.WriteLine("end if;");
                OutVHDL.WriteLine();
                OutVHDL.WriteLine("end process;");
                OutVHDL.WriteLine();
                OutVHDL.WriteLine("comb : process (input, current_state)");
                OutVHDL.WriteLine("begin");
                OutVHDL.WriteLine();
                OutVHDL.WriteLine("case current_state is");
                foreach (Transition trans in transitions)
                {
                    string source = FindStateName(trans.source);
                    string destination = FindStateName(trans.destination);
                    OutVHDL.WriteLine("when " + source + " =>");
                    OutVHDL.Write("state_out <= ");
                    OutVHDL.WriteLine("\"" + label2number[trans.source] + "\"");
                    OutVHDL.WriteLine("if ( input = '" + trans.label + "' )");
                    OutVHDL.WriteLine("then next_state <= " + destination + ";");
                    OutVHDL.WriteLine("else next_state <= " + source + ";");
                    OutVHDL.WriteLine("end if;");
                    OutVHDL.WriteLine();
                }
                OutVHDL.WriteLine("end case;");
                OutVHDL.WriteLine("end process;");
                OutVHDL.WriteLine();
                OutVHDL.WriteLine("end Behavioral;");
            }
            Done.Visibility = Visibility.Hidden;
        }
    }
}
