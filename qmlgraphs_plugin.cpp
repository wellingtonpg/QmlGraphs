#include <qqml.h>

#include "qmlgraphs_plugin.h"

#include "src/utils.h"
#include "src/pie.h"
#include "src/piemodel.h"
#include "src/slice.h"

void QmlGraphsPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Pie>(uri, 1, 0, "Pie");
    qmlRegisterType<PieModel>(uri, 1, 0, "PieModel");
    qmlRegisterType<Slice>(uri, 1, 0, "Slice");
    qmlRegisterType<LegendAlignment>(uri, 1, 0, "LegendAlignment");
}


