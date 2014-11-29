Curves Editor Program Functionality
Emma Meersman
Graphics

Implemented functionality of curve editor:

1. Supports Polylines (pink) as well as Lagrange (green) and Bezier (red) curves.
2. Selected objects are colored blue and have double width.
3. The user can create objects by pressing down the 'P', 'L', or 'B' key --- Polyline, Lagrange, or Bezier, respectively. Control points can be added by mouse clicks as long as the key is held down. Releasing the key deletes the selected object if it has less then two control points. The object being created is always the selected one, and is drawn as such. The control points of the selected curve are also drawn.
4. Pressing SPACE makes the next object selected instead of the current one, repeatedly pressing SPACE cycles over all curves.
5. When no keys are pressed and the user presses the mouse button, the object approximately at the mouse cursor (if there is any) becomes selected.
6. As long as the mouse button remains pressed, mouse movements drag the selected object. When the button is released, the object remains selected.
7. When an object is selected, the user may hold down 'A' to add control points to the selected object by clicking.
8. Support removing control points of the selected curve, by holding 'D' and clicking them.
9. When an object is selected, pressing the 'F' key should turn the curve into a polygon that fills the curve. This works for convex shapes.
10. Supports Catmull-Clark subdivision curves, created by pressing 'C' when a Polyline is selected.
11. Displays the current number of curves in the corner using Bezier curves to form the numbers.

(The wording of some listed functionality has been copied from the assignment text)