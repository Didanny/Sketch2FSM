using System;

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

        // Constructor
        public State(int lbl, string n, double xx, double yy, double r)
        {
            label = lbl;
            name = n;
            x = xx;
            y = yy;
            radius = r;
        }

        // Draw
        public void Draw(Canvas canvas)
        {
            throw new NotImplementedException();
        }
    }
}
