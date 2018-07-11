#ifndef __HDMAYA_MATERIAL_ADAPTER_H__
#define __HDMAYA_MATERIAL_ADAPTER_H__

#include <pxr/pxr.h>

#include <hdmaya/adapters/adapter.h>

PXR_NAMESPACE_OPEN_SCOPE

class HdMayaMaterialAdapter : public HdMayaAdapter {
public:
    HDMAYA_API
    HdMayaMaterialAdapter(const MObject& node, HdMayaDelegateCtx* delegate);
    HDMAYA_API
    virtual ~HdMayaMaterialAdapter() = default;

    HDMAYA_API
    bool IsSupported() override;

    HDMAYA_API
    bool HasType(const TfToken& typeId) override;

    HDMAYA_API
    void MarkDirty(HdDirtyBits dirtyBits) override;
    HDMAYA_API
    void RemovePrim() override;
    HDMAYA_API
    void Populate() override;
};

using HdMayaMaterialAdapterPtr = std::shared_ptr<HdMayaMaterialAdapter>;

PXR_NAMESPACE_CLOSE_SCOPE

#endif // __HDMAYA_MATERIAL_ADAPTER_H__
