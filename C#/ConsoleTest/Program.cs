using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Diagnostics;
using Sketch2FSM_UI;

namespace ConsoleTest
{
    class Program
    {

        [DllImport("C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\C#\\sketch2fsmlib\\x64\\Debug\\sketch2fsmlib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Start();

        public static List<IDrawable> components;

        static void Main(string[] args)
        {
            // Starting the Sketch2FSM.exe
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.CreateNoWindow = false;
            startInfo.UseShellExecute = false;
            startInfo.FileName = "C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\OpenCVtest\\OpenCVtest\\OpenCVtest.exe";
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.Arguments = "\"C:\\Users\\Danny\\Desktop\\AUB\\EECE 437\\test2.jpg\"";

            using (Process exeProcess = Process.Start(startInfo))
            {
                exeProcess.WaitForExit();
            }

            components = new List<IDrawable>();

            // Reading from the output file
            string line;
            string[] splitted;
            System.IO.StreamReader file = new System.IO.StreamReader(@"./output.txt");

            line = file.ReadLine();
            splitted = line.Split(',');

            System.Console.WriteLine(Int32.Parse(splitted[0]));
            System.Console.WriteLine(Int32.Parse(splitted[1]));

            while ((line = file.ReadLine()) != null)
            {
                splitted = line.Split(',');
                if (splitted[0].Equals("T"))
                {
                    Console.WriteLine("T");
                    Console.WriteLine(Int32.Parse(splitted[1]));
                    Console.WriteLine(Int32.Parse(splitted[1]));
                    Console.WriteLine(splitted[3]);
                    Console.WriteLine(Double.Parse(splitted[4]));
                    Console.WriteLine(Double.Parse(splitted[5]));
                    Console.WriteLine(Double.Parse(splitted[6]));
                    Console.WriteLine(Double.Parse(splitted[7]));
                    //components.Add(new Transition(Int32.Parse(splitted[1]), Int32.Parse(splitted[1]), splitted[3], Double.Parse(splitted[4]), Double.Parse(splitted[5]), Double.Parse(splitted[6]), Double.Parse(splitted[7])));
                }
                else
                {
                    Console.WriteLine("S");
                    Console.WriteLine(splitted[1]);
                    Console.WriteLine(splitted[2]);
                    Console.WriteLine(splitted[3]);
                    Console.WriteLine(splitted[4]);
                    Console.WriteLine(splitted[5]);
                    //components.Add(new State(Int32.Parse(splitted[1]), splitted[2], Double.Parse(splitted[3]), Double.Parse(splitted[4]), Double.Parse(splitted[5])));
                }
                //System.Console.WriteLine(line);
            }
        }
    }
}
