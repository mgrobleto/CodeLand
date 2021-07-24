import { TabTemplates } from "./templates.js";

class TabUI extends TabTemplates {
    constructor() {
        super();
        this.$containerTab = document.getElementById("editor-group");
    }

    render(tabs, key = null) {
        const tabArray = [];

        tabs.forEach((tab) => {
            tabArray.push(this.templateTab(tab));
        });

        this.$containerTab.innerHTML = "";
        this.$containerTab.append(...tabArray);

        if (!key) {
            tabArray.forEach((element) => {
                if (element.classList.contains("active") === true) {
                    element.children[1].click();
                }
            });
        } else {
            tabs.forEach((tab, index) => {
                if(tab.key === key) {
                    tabArray[index].children[1].click();
                }
            })
        }
    }
}

export default new TabUI();
