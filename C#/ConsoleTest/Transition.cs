using System;

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

        // Constructor
        public Transition(int s, int d, string lbl, double sx, double sy, double dx, double dy)
        {
            source = s;
            destination = d;
            label = lbl;
            source_x = sx;
            source_y = sy;
            destination_x = dx;
            destination_y = dy;
        }

        // Draw
        public void Draw(Canvas canvas)
        {
            throw new NotImplementedException();
        }
    }
}
