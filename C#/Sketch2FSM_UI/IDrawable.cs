using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace Sketch2FSM_UI
{
    public interface IDrawable
    {
        //void Draw(Point location);
        void Draw(Canvas canvas, SolidColorBrush color);
        bool Equals(IDrawable drawable);
    }
}
