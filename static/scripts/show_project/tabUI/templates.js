import { deleteTab, activeTab } from "../action/index.js";
import storage from "../utils/storage.js";

function getStyle(styles) {
    const $tagStyle =
    document.querySelector("[data-style-code]") ||
    document.createElement("style");

    if (!$tagStyle.getAttribute("[data-style-code]")) {
        $tagStyle.setAttribute("data-style-code", true);
        $tagStyle.appendChild(document.createTextNode(styles));
        document.head.appendChild($tagStyle);
    } else {
        $tagStyle.innerHTML = styles;
    }


}

class TabTemplates {
    constructor() {

    }

    templateTab({ filename, key, code, isActive }) {
        const container = document.createElement("div");
        const closeTab = document.createElement("div");
        const tagI = document.createElement("i");
        const filenameContainer = document.createElement("div");
        const p = document.createElement("p");

        container.className = "tab" + (isActive ? " active" : "");
        container.dataset.ref = key;
        closeTab.className = "close-tab";
        filenameContainer.className = "filename";
        
        // eliminamos el tab
        closeTab.addEventListener("click", async function () {
            const store = storage.getStore();
            const tabContainer = this.parentNode;
            console.log('D:')

            if (tabContainer.classList.contains("active")) {
                const $containerTab = document.getElementById("editor-group");

                // console.log(store)
                if((store.length - 1) > 0) {
                    store.forEach((tab, index) => {
                        if (tab.key == key) {
                            const indexOf = index > 0 ? index - 1 : store.length - 1
                            const beforeTab = store[indexOf];
                            const nodeStylesTemp = beforeTab.code.css;
                            
                            getStyle(nodeStylesTemp);
                            $containerTab.children[indexOf].children[1].click();
                            tabContainer.remove();
                        }
                    });
                } else {
                    const $showCode = document.querySelector("#show_code");
                    $showCode.innerHTML = ''
                    tabContainer.remove();
                }
            } else {
                tabContainer.remove();
            }
            await storage.dispatch(deleteTab(key));
        });

        tagI.innerHTML = `
        <img loading="lazy" width="14px" src="/static/icons/close-icon.svg" alt="Cerrar archivo">
        `;
        p.innerHTML = filename;

        filenameContainer.addEventListener('click',function () {
            const $containerTab = document.getElementById("editor-group");

            Array.prototype.forEach.call(
                $containerTab.children,
                function (tab) {
                    if (tab.classList.contains("active")) {
                        tab.classList.remove("active");
                    }
                }
            );

            if (!$containerTab.classList.contains("active")) {
                const $showCode = document.querySelector("#show_code");
                
                getStyle(code.css)
                $showCode.innerHTML = code.html;
            }

            container.classList.toggle("active");
            storage.dispatch(activeTab(key));
        });

        closeTab.appendChild(tagI);
        container.appendChild(closeTab);
        filenameContainer.appendChild(p);
        container.appendChild(filenameContainer);

        return container;
    }
}

export { TabTemplates };
