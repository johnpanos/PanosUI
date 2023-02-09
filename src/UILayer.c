
#include <stdlib.h>
#include <string.h>
#include "UILayer.h"

void UILayerAddSublayer(UILayer layer, UILayer sublayer) {
    ArrayAddValue(layer->sublayers, sublayer);
}

UILayer UILayerGetInFlight(UILayer layer) {
    UILayer copied;
    memcpy(copied, layer, sizeof(struct _UILayer));
}