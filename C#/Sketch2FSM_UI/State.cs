using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Sketch2FSM_UI
{
    class State : IDrawable
    {
        // State label, from the connectedComponents
        public int label;

        // State name
        public string name;

        // Sate coordinates and radius
        public double x;
        public double y;
        public double radius;

        // public bool
        public bool is_accept;

        // State circle
        private Ellipse circle;
        public Ellipse Circle { get => circle; set => circle = value; }

        // Constructor from text file
        public State(int lbl, string n, double xx, double yy, double r)
        {
            label = lbl;
            name = n;
            x = xx;
            y = yy;
            radius = r;

            Circle = new Ellipse
            {
                StrokeThickness = 2,
                Margin = new Thickness((x - radius) * ImageDimensions.Panel.width / ImageDimensions.Image.width, (y - radius) * ImageDimensions.Panel.height / ImageDimensions.Image.height, 0, 0),
                Height = (radius * 2) * ImageDimensions.Panel.height / ImageDimensions.Image.height,
                Width = (radius * 2) * ImageDimensions.Panel.width / ImageDimensions.Image.width
            };

            is_accept = false;
        }

        // Construtor from user input
        public State(int lbl, string n, Ellipse c)
        {
            label = lbl;
            name = n;
            Circle = c;

            is_accept = false;
        }

        // Set accept
        public void SetAccept()
        {
            is_accept = true;
        }
        
        // Set not accept
        public void SetNotAccept()
        {
            is_accept = false;
        }

        // Draw
        public void Draw(Canvas canvas, SolidColorBrush color)
        {
            Circle.Stroke = color;
            TextBlock Name = new TextBlock
            {
                Text = name,
                Margin = new Thickness(Circle.Margin.Left + Circle.Width / 2.2, Circle.Margin.Top + Circle.Height / 2.2, 0, 0)
            };
            canvas.Children.Add(Circle);
            canvas.Children.Add(Name);
        }

        // Equality comparison
        public bool Equals(IDrawable drawable)
        {
            if (drawable is State)
            {
                State state = (State)drawable;
                if (label == state.label &&
                    name == state.name &&
                    Circle.Width == state.Circle.Width &&
                    Circle.Height == state.Circle.Height && 
                    Circle.Margin.Equals(state.Circle.Margin))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
}
