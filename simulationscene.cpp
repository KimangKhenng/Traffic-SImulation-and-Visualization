#include "simulationscene.h"

SimulationScene::SimulationScene()
{
    /////////////////
    ///
    /// Set Index Method of How QGraphicsScene
    /// Should manage item
    /// NoIndex is good for dynamic scene
    setItemIndexMethod(QGraphicsScene::NoIndex);
    /////////////////
    ///
    /// Set background brush for scene
    setBackgroundBrush (Qt::Dense5Pattern);
}
