#ifndef DSTEPWMXCBACTIONFACTORY_H
#define DSTEPWMXCBACTIONFACTORY_H

#include <actionfactory.h>

#include <QObject>
#include <QVariant>

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbActionFactory : public QObject, public ActionFactory
{
    Q_OBJECT
    Q_INTERFACES(dstep::wm::interfaces::ActionFactory)
public:
    explicit DstepWmXcbActionFactory(QObject *parent = 0);

signals:

public slots:

    // ActionFactory interface
public:
    virtual Action *createAction(int type, const QVariant &actionParams) const;
};

} // namespace wm
} // namespace dstep

#endif // DSTEPWMXCBACTIONFACTORY_H
