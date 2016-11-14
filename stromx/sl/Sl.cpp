#include "stromx/sl/Sl.h"

#include <iostream>
#include <stromx/runtime/Exception.h>
#include <stromx/runtime/Locale.h>
#include <stromx/runtime/Registry.h>

#include "stromx/sl/Decode.h"
#include "stromx/sl/Encode.h"
#include "stromx/sl/OpenGlProjector.h"

namespace stromx
{
    namespace sl
    {
        std::locale locale;
    }
}

int stromxRegisterSl(stromx::runtime::Registry* registry)
{
    using namespace stromx::sl;
    
    locale = stromx::runtime::Locale::generate(STROMX_SL_LOCALE_DIR, STROMX_SL_LOCALE_DOMAIN);
    
    try
    {
        registry->registerOperator(new Decode);  
        registry->registerOperator(new Encode);  
        registry->registerOperator(new OpenGlProjector);
    }
    catch(stromx::runtime::Exception & e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
