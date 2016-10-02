#ifndef STROMX_SL_ZBAR_H
#define STROMX_SL_ZBAR_H

#include "stromx/sl/Config.h"

namespace stromx
{
    namespace runtime
    {
        class Registry;
    }
}

extern "C"
{
    STROMX_SL_API int stromxRegisterSl(stromx::runtime::Registry* registry);
}

#endif // STROMX_SL_ZBAR_H
