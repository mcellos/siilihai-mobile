import QtQuick 2.0
import "forum"
import "account"

Rectangle {
    width: 600
    height: 1024
    color: "white"
    property string color1: "#7d7dc0"
    property string color2: "#ffd884"
    property string colorDark: "#003e5e"
    property string colorLessDark: "#407e9e"

    ForumListView {
        id: forumListView
        property bool topItem: !threadListView.topItem && !messageListView.topItem
        width: parent.width
        height: parent.height - toolbar.height
        HideEffect {}
    }
    ThreadListView {
        id: threadListView
        property bool topItem: siilihaimobile.selectedGroupId
        width: parent.width
        height: parent.height - toolbar.height
        x: topItem ? 0 : parent.width
        Behavior on x { SmoothedAnimation { velocity: 1500; easing.type: Easing.InOutQuad  } }
        HideEffect {}
    }
    MessageListView {
        id: messageListView
        property bool topItem: siilihaimobile.selectedThreadId
        width: parent.width
        height: parent.height - toolbar.height
        x: topItem ? 0 : parent.width
        Behavior on x { SmoothedAnimation { velocity: 1500; easing.type: Easing.InOutQuad  } }
        HideEffect {}
    }
    LoginWizard {
        width: parent.width
        height: parent.height - toolbar.height
    }
    SubscribeForumDialog {
        id: subscribeForumDialog
        width: parent.width
        height: parent.height - toolbar.height
        Behavior on x { SmoothedAnimation { velocity: 1500; easing.type: Easing.InOutQuad  } }
    }

    Toolbar {
        id: toolbar
        anchors.bottom: parent.bottom
    }

    ForumSettingsDialog {
        id: forumSettingsDialog
        objectName: "forumSettingsDialog"

        Behavior on x { SmoothedAnimation { velocity: 1500; easing.type: Easing.InOutQuad  } }
        HideEffect {}
    }
    MessageDialog {}
}