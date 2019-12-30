#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/components/I_BLDC.hpp"
class BLDC_fake : public I_BLDC, public Component {
public:
    BLDC_fake(Component*, const char*, const char*);
    virtual ~BLDC_fake(){};
    void init();
    void update();
    
};