import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle{
    property color backgroundColor:"transparent"
    property color hoveredBackgroundColor:"#F04830"
    property color pressedBackgroundColor:"#F03018"
    property color normalBackgroundColor:"transparent"

    property color hoveredLineColor: "#FFFFFF"
    property color pressedLineColor: "#F9DEDE"
    property color normalLineColor: "#AAFFFFFF"
    property color lineColor:"#AAFFFFFF"

    property color normalLineColorGray:"#9A9DA3"
    property color pressedLineColorGray:"#6E7075"
    property color hoveredLineColorGray:"#828489"

    property int enumCurrentIconType:RCIconButton.IconType.TYPE_CLOSE

    property bool bIsRadius:false
    property size g_sizeCanva:Qt.size(13, 13)

    enum IconType
    {
        TYPE_CLOSE,
        TYPE_MINI,
        TYPE_SEEK,
        TYPE_MENU,
        TYPE_NOBACKCLOSE
     }

    signal buttonClicked()

    color:backgroundColor
    radius: bIsRadius?4:0

    Canvas{
        id:canvas
        width: g_sizeCanva.width
        height: g_sizeCanva.height
        anchors.centerIn: parent
        visible: true
        onPaint:{
            var ctx = getContext("2d")
            ctx.clearRect(0,0,width,height)
            ctx.save()
            ctx.strokeStyle = lineColor
            ctx.lineWidth = 2;
            ctx.beginPath()
            if(enumCurrentIconType === RCIconButton.IconType.TYPE_CLOSE ||
               enumCurrentIconType === RCIconButton.IconType.TYPE_NOBACKCLOSE)
            {
                ctx.moveTo(0,0)
                ctx.lineTo(width,height)
                ctx.moveTo(width,0)
                ctx.lineTo(0,height)
            }
            else if(enumCurrentIconType === RCIconButton.IconType.TYPE_MINI)
            {
                ctx.moveTo(0,height/2+3)
                ctx.lineTo(width,height/2+3)
            }
            else if(enumCurrentIconType === RCIconButton.IconType.TYPE_SEEK)
            {
                ctx.lineWidth = 1.5;
                ctx.beginPath()
                ctx.arc(width/2,height/2-1,5,0,360*Math.PI/180,true)
                ctx.moveTo(width/2+3,height/2+2)
                ctx.lineTo(width,height-1)
            }
            else if(enumCurrentIconType === RCIconButton.IconType.TYPE_MENU)
            {
                ctx.lineWidth = 1;
                ctx.fillStyle = lineColor
                ctx.arc(width/2,height*1/4,2,0,360*Math.PI/180)
                ctx.moveTo(width/2,height*2/4)
                ctx.arc(width/2,height*2/4,2,0,360*Math.PI/180)
                ctx.moveTo(width/2,height*3/4)
                ctx.arc(width/2,height*3/4,2,0,360*Math.PI/180)
            }

            ctx.fill();  //填充
            ctx.stroke()
            ctx.restore()
        }
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled:true

        onClicked: {
            if(enumCurrentIconType === RCIconButton.IconType.TYPE_CLOSE)
            {
                backgroundColor = hoveredBackgroundColor
            }

            if(enumCurrentIconType === RCIconButton.IconType.TYPE_NOBACKCLOSE)
            {
                lineColor = hoveredLineColorGray
            }
            else
            {
                lineColor = hoveredLineColor
            }

            canvas.requestPaint()
            buttonClicked()
        }

        onPressed:{
            if(enumCurrentIconType === RCIconButton.IconType.TYPE_CLOSE)
            {
                backgroundColor = pressedBackgroundColor
            }

            if(enumCurrentIconType === RCIconButton.IconType.TYPE_NOBACKCLOSE)
            {
                lineColor = pressedLineColorGray
            }
            else
            {
                lineColor = pressedLineColor
            }

            canvas.requestPaint()
        }

        onEntered:{
            if(enumCurrentIconType === RCIconButton.IconType.TYPE_CLOSE)
            {
                backgroundColor = hoveredBackgroundColor
            }

            if(enumCurrentIconType === RCIconButton.IconType.TYPE_NOBACKCLOSE)
            {
                lineColor = hoveredLineColorGray
            }
            else
            {
                lineColor = hoveredLineColor
            }

            canvas.requestPaint()
        }

        onExited:{
            if(enumCurrentIconType === RCIconButton.IconType.TYPE_CLOSE)
            {
                backgroundColor = normalBackgroundColor
            }

            if(enumCurrentIconType === RCIconButton.IconType.TYPE_NOBACKCLOSE)
            {
                lineColor = normalLineColorGray
            }
            else
            {
                lineColor= normalLineColor
            }

            canvas.requestPaint()
        }
    }
}
