#include <QDialog>

namespace Ui
{
    class Finish;
}
namespace webidl2cpp_application
{
    class Finish : public QDialog
    {
        Q_OBJECT

    public:
        explicit Finish(QWidget *parent = 0);
        ~Finish();

    private:
        Ui::Finish *ui;
    };
}
