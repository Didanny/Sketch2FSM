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
    class Transition : IDrawable
    {
        // Source state and destination state by label
        public int source;
        public int destination;

        // Transition input required to go to next state
        public string label;

        // Coordinates
        public double source_x;
        public double source_y;
        public double destination_x;
        public double destination_y;

        // Transition arrow
        private Line arrow;
        private Ellipse head;

        public Ellipse Head { get => head; set => head = value; }
        public Line Arrow { get => arrow; set => arrow = value; }

        // Constructor from text file
        public Transition(int s, int d, string lbl, double sx, double sy, double dx, double dy)
        {
            source = s;
            destination = d;
            label = lbl;
            source_x = sx;
            source_y = sy;
            destination_x = dx;
            destination_y = dy;

            Arrow = new Line
            {
                StrokeThickness = 2,
                X1 = source_x * ImageDimensions.Panel.width / ImageDimensions.Image.width,
                X2 = destination_x * ImageDimensions.Panel.width / ImageDimensions.Image.width,
                Y1 = source_y * ImageDimensions.Panel.height / ImageDimensions.Image.height,
                Y2 = destination_y * ImageDimensions.Panel.height / ImageDimensions.Image.height
            };
            Head = new Ellipse
            {
                StrokeThickness = 2,
                Margin = new Thickness(Arrow.X2, Arrow.Y2, 0, 0),
                Height = 5,
                Width = 5
            };
        }

        // Constructor from user input
        public Transition(int s, int d, string lbl, Line a, Ellipse h)
        {
            source = s;
            destination = d;
            Arrow = a;
            Head = h;
        }

        // Draw
        public void Draw(Canvas canvas, SolidColorBrush color)
        {
            Arrow.Stroke = color;
            Head.Stroke = color;

            canvas.Children.Add(Arrow);
            canvas.Children.Add(Head);
            //throw new NotImplementedException();
        }

        // Equals comparison
        public bool Equals(IDrawable drawable)
        {
            if (drawable is Transition)
            {
                Transition trans = (Transition)drawable;
                if (label == trans.label &&
                    Arrow.X1 == trans.Arrow.X1 &&
                    Arrow.X2 == trans.Arrow.X2 &&
                    Arrow.Y1 == trans.Arrow.Y1 &&
                    Arrow.Y2 == trans.Arrow.Y2)
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
