#include "VBaseSplitter.h"


VBaseSplitter::VBaseSplitter(QWidget *parent) : QWidget(parent)
{

}

void VBaseSplitter::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)

    if(!m_bIsInit){
        initUI();
        m_bIsInit = true;
    }
}

void VBaseSplitter::initUI()
{
//    this->setObjectName("WidgetMain");

    /*初始化一个主分割器 和 一个主文本编辑器*/
    m_pSplitterMain = creatSplitter(Qt::Vertical,this);
    m_pSplitterMain->setObjectName("SplitterMain");

    m_pFormMain = creatForm(m_pSplitterMain); //初始化创建一个
    m_pFormMain->setObjectName("FormMain");

    //初始选中
    VBaseSplitterForm *pMain = qobject_cast<VBaseSplitterForm *>(m_pFormMain);
    pMain->setFormChecked(true);

    m_pSelectedForm = m_pFormMain; //初始化

    QHBoxLayout *pMainLayout = new QHBoxLayout(this);
    pMainLayout->setContentsMargins(0,0,0,0);
    pMainLayout->addWidget(m_pSplitterMain);
}

QSplitter *VBaseSplitter::creatSplitter(Qt::Orientation orientation, QWidget *parent)
{
    QSplitter *splitter = new QSplitter(orientation,parent);
    splitter->setObjectName("splitter" + QString::number(m_plistSplitter.size()));
    splitter->setHandleWidth(3);
    m_plistSplitter.append(splitter);

    return splitter;
}

QWidget *VBaseSplitter::creatForm(QWidget *parent)
{
    QWidget *pWidget = newForm(parent);
    VBaseSplitterForm *pForm = qobject_cast<VBaseSplitterForm *>(pWidget);
    connect(pForm,&VBaseSplitterForm::sigFormSelected,[=]{
        VBaseSplitterForm *pS = qobject_cast<VBaseSplitterForm *>(m_pSelectedForm);
        pS->setFormChecked(false);
        pForm->setFormChecked(true);
        m_pSelectedForm = pForm;
        emit sigSelected(m_pSelectedForm);
    });

    pWidget->setObjectName("form" + QString::number(m_listForm.size()));

    m_listForm.append(pWidget);

    emit sigNewForm(pWidget);

    return pWidget;
}

QWidget *VBaseSplitter::newForm(QWidget *parent)
{
//    qDebug()<<"创建一个默认部件";
    return new QWidget(parent);
}

void VBaseSplitter::removeForm(QWidget *rmForm)
{
    if((nullptr == rmForm) || (0 == m_listForm.count()))
        return ;

    /*遍历链表  删除项*/
    QWidget *tmpTextEditor;
    foreach(tmpTextEditor,m_listForm){
        if(tmpTextEditor == rmForm)
        {
            m_listForm.removeOne(rmForm);
            delete rmForm;
//            qDebug()<<"从链表里删除一个Editor!";
//            qDebug()<<"还有：" <<m_listForm.count()<<" 个textEditor";

            foreach(tmpTextEditor,m_listForm){
//                qDebug()<<"还存在的textEditor: "<< tmpTextEditor->objectName();
            }

            return;
        }
    }
}

void VBaseSplitter::removeSplitter(QSplitter *rmSplitter)
{
    if((nullptr == rmSplitter) || (0 == m_plistSplitter.count()))
        return ;

    /*遍历链表  删除项*/
    QSplitter *tmpSplitter;
    foreach(tmpSplitter,m_plistSplitter){
        if(tmpSplitter == rmSplitter)
        {
            m_plistSplitter.removeOne(rmSplitter);
            delete rmSplitter;
//            qDebug()<<"从链表里删除一个Splitter!";
//            qDebug()<<"还有：" << m_plistSplitter.count() <<" 个Splitter";

            /*调试*/
            foreach(tmpSplitter,m_plistSplitter){
//                qDebug()<<"还存在的Splitter: "<< tmpSplitter->objectName();
            }

            return;
        }
    }

}

void VBaseSplitter::slotVSplitScreen()
{
    // Qt::Vertical   垂直
    // Qt::Horizontal 水平
//    qDebug("垂直分屏");

    if(nullptr == m_pSelectedForm)
        return ;

    m_pParentSplitter = qobject_cast<QSplitter *>(m_pSelectedForm->parentWidget());
    if(nullptr == m_pParentSplitter)
        return ;

    /*m_pParentSplitter
      * 1.如果是水平分割器 设置为垂直分割器  是垂直分割器不用管
      * 2.new 两个垂直分割器(水平分割器也可以 因为无法预料下次分割是水平还是垂直)
      * 3.将 m_pSelectedForm(当前选中的编辑器) 移到其中一个分割器
      * 4.new 一个编辑器 到另一个分割器
      * 5.添加这两个分割器到 m_pParentSplitter(选中编辑器所在的分割器中) */

    if(Qt::Vertical != m_pParentSplitter->orientation()){
//        qDebug("所在Splitter是水平分割器!");
        m_pParentSplitter->setOrientation(Qt::Vertical); //设置为垂直分割器
    }

    QSplitter *splitterFirst = creatSplitter(Qt::Vertical,m_pParentSplitter);
    QSplitter *splitterSecond = creatSplitter(Qt::Vertical,m_pParentSplitter);

    m_pSelectedForm->setParent(splitterFirst);

    creatForm(splitterSecond);

    m_pParentSplitter->addWidget(splitterFirst);
    m_pParentSplitter->addWidget(splitterSecond);

    /*设置分割比例  目前无效  @bug*/
    m_pParentSplitter->setStretchFactor(0,1);
    m_pParentSplitter->setStretchFactor(1,1);
}

void VBaseSplitter::slotHSplitScreen()
{
//    qDebug("水平分屏");
    if(nullptr == m_pSelectedForm)
        return ;

    m_pParentSplitter = qobject_cast<QSplitter *>(m_pSelectedForm->parentWidget());
    if(nullptr == m_pParentSplitter)
        return ;

    /*m_pParentSplitter
     * 1.如果垂直分割器 设置为水平分割器 水平则不设置
     * 2.new 两个水平分割器(垂直分割器也可以 因为无法预料下次分割是水平还是垂直)
     * 3.将 m_pSelectedForm(当前选中的编辑器) 移到其中一个分割器
     * 4.new 一个编辑器 到另一个分割器
     * 5.添加这两个分割器到 m_pParentSplitter(选中编辑器所在的分割器中) */
    if(Qt::Horizontal != m_pParentSplitter->orientation()){
//        qDebug("所在Splitter是垂直分割器!");
        m_pParentSplitter->setOrientation(Qt::Horizontal); //设置为 水平 分割器
    }

    QSplitter *splitterFirst = creatSplitter(Qt::Horizontal,m_pParentSplitter);
    QSplitter *splitterSecond = creatSplitter(Qt::Horizontal,m_pParentSplitter);

    m_pSelectedForm->setParent(splitterFirst);

    creatForm(splitterSecond);

    m_pParentSplitter->addWidget(splitterFirst);
    m_pParentSplitter->addWidget(splitterSecond);

    /*设置分割比例  目前无效  @BUG*/
    m_pParentSplitter->setStretchFactor(0,1);
    m_pParentSplitter->setStretchFactor(1,1);
}

void VBaseSplitter::slotMergeScreen()
{
    /* 大于两个编辑器的分屏策略
     * QSplitter Grandgrandfather,*Grandpa,*uncle,*parent;
     * QWidget *brother *Me *uncleEditor;
     *    -----------------------------------------------------
     *  |                  Grandgrandfather                    |
     *  |  -----------------------------   -----------------   |
     *  | |          Grandpa            | |    Grandpa      |  |
     *  | |  -----------   -----------  | |    ---------    |  |
     *  | | |  uncle    | |   parent  | | |   |         |   |  |
     *  | | |  -------  | |  -------  | | |   | uncle   |   |  |
     *  | | | |brother| | | |   Me  | | | |   | Editor  |   |  |
     *  | | |  -------  | |  -------  | | |   |         |   |  |
     *  | | |           | |           | | |    ---------    |  |
     *  | |  -----------   -----------  | |                 |  |
     *  |  -----------------------------   -----------------   |
     *   ------------------------------------------------------
     * 大于两个编辑器删除分屏策略
     * 1.找到 叔叔对象
     * 2.把 叔叔对象 放入祖父里
     * 3.删除选中编辑器、父亲、爷爷
     */


    /* 剩余两个编辑器的分屏状态
     * QWidget *Grandgrandfather;
     * QSplitter *Grandpa,*uncle,*parent;
     * QWidget *brother *Me *uncleEditor;
     *    -----------------------------------------------------
     *  |                  Grandgrandfather                    |
     *  |  -----------------------------   -----------------   |
     *  | |          Grandpa            | |    Grandpa      |  |
     *  | |  -----------   -----------  | |    ---------    |  |
     *  | | |  uncle    | |   parent  | | |   |         |   |  |
     *  | | |  -------  | |  -------  | | |   | uncle   |   |  |
     *  | | | |brother| | | |   Me  | | | |   | Editor  |   |  |
     *  | | |  -------  | |  -------  | | |   |         |   |  |
     *  | | |           | |           | | |    ---------    |  |
     *  | |  -----------   -----------  | |                 |  |
     *  |  -----------------------------   -----------------   |
     *   ------------------------------------------------------
     * 剩余两个编辑器删除分屏策略
     * 1.找到 叔叔对象、兄弟编辑器
     * 2.把 兄弟编辑器放入爷爷里
     * 3.删除选中编辑器、父亲、爷爷
     */

    /*当前未选中窗口  或者只有一个Editor 不操作  退出*/
    if((nullptr == m_pSelectedForm) || (1 == m_listForm.count()))
        return ;


    m_pParentSplitter = qobject_cast<QSplitter *>(m_pSelectedForm->parentWidget());   //获取父对象
    m_pGrandpaSplitter = qobject_cast<QSplitter *>(m_pParentSplitter->parentWidget());      //获取爷爷对象
    m_pGrandgrandfather = m_pGrandpaSplitter->parentWidget();                               //获取曾祖父

    if((nullptr == m_pParentSplitter) || (nullptr == m_pGrandpaSplitter) || (nullptr == m_pGrandgrandfather))
        return ;

    /*遍历爷爷对象  找到叔叔对象*/
    for(int i = 0; i < m_pGrandpaSplitter->count(); i++)
    {
        /*每个 爷爷Splitter 里只有两个子对象 */
        if(m_pParentSplitter->objectName() != m_pGrandpaSplitter->widget(i)->objectName()){
            m_pUncleSplitter = qobject_cast<QSplitter *>(m_pGrandpaSplitter->widget(i));
        }
    }

    /*选中编辑器祖父不是Splitter 是主背景Widget 的删除方法*/
    /* 1.删除自己和父亲
     */
    if(m_pSplitterMain ==  m_pGrandpaSplitter)
    {
        removeForm(m_pSelectedForm);
        removeSplitter(m_pParentSplitter);

        m_pSelectedForm = m_listForm.last();
        //选中控件
        VBaseSplitterForm *pS = qobject_cast<VBaseSplitterForm *>(m_pSelectedForm);
        if(nullptr != pS)
            pS->setFormChecked(true);
//        qDebug()<<"执行删除策略1";
        return ;
    }
    /*大于两个编辑器的删除方法*/
    else
    {
        QSplitter * splitterGrandFather = qobject_cast<QSplitter *>(m_pGrandgrandfather);
        if(nullptr != splitterGrandFather){
            //爷爷index是0 就把叔叔放到0 防止直接放入祖父之后引起布局变化
            if(0 == splitterGrandFather->indexOf(m_pGrandpaSplitter))
                splitterGrandFather->insertWidget(0,m_pUncleSplitter);
            else
                splitterGrandFather->insertWidget(1,m_pUncleSplitter);
        }

        removeForm(m_pSelectedForm);
        removeSplitter(m_pParentSplitter);
        removeSplitter(m_pGrandpaSplitter);

        m_pSelectedForm = m_listForm.last();
        //选中控件
        VBaseSplitterForm *pS = qobject_cast<VBaseSplitterForm *>(m_pSelectedForm);
        if(nullptr != pS)
            pS->setFormChecked(true);
        m_pParentSplitter = nullptr;
        m_pGrandpaSplitter = nullptr;
//        qDebug()<<"执行删除策略2";
        return ;
    }
}
