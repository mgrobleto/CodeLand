"use strict";
import tabUI from "../tabUI/tab.js";
import storage from '../utils/storage.js'
import { setTab } from '../action/index.js'

class ListDirTemplate {
    
    constructor() {
        this.listDir = [];
        this.$showCode = document.querySelector("#show_code");
        this.CURRENT_PATH = location.pathname;
        this.$nodeStyle = null;
    }

    /**
     * @param {Array} elements
     * Nombres de los archivos del directorio
     * @param {Array} paths
     * La dirección del archivo en firebase
     * @returns { String }
     */
    async handleClick(filename, path) {
        const file = {
            filename,
            path
        };
        
        const response = await fetch(this.CURRENT_PATH, {
            method: 'POST',
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(file)
        });
        const responseJson = await response.json();
        
        if(responseJson.type == 'code') {
            const store = storage.getStore()
            const $tagStyle = document.querySelector('[data-style-code]') || document.createElement("style");
            const tempStyle = responseJson.code.css
            const key = path + filename;

            if(!$tagStyle.getAttribute('[data-style-code]')) {
                $tagStyle.appendChild(document.createTextNode(tempStyle));
                $tagStyle.setAttribute('data-style-code', true);
                document.head.appendChild($tagStyle);
            } else {
                $tagStyle.innerHTML = responseJson.code.css;
            }
            
            
            this.$showCode.innerHTML = responseJson.code.html;
            if(store && !store.find(tab => tab.key === key)) {
                storage.dispatch(setTab({
                    ...file,
                    key,
                    code: {
                        html: responseJson.code.html,
                        css: responseJson.code.css
                    },
                    isActive: true
                }))
                tabUI.render(storage.getStore());
            }
        } else {
            // let parse_binary = new Uint8Array(responseJson.file);
            let binaryInfo = JSON.parse(responseJson.image);
            const ext = responseJson.info.file_ext
            const type = responseJson.info.type;
            
            this.$showCode.innerHTML = `
                <img loading="lazy" src="data:${type}/${ext};base64,${atob(binaryInfo.$binary)}" alt="${ext}" />
            `.trim();
        }

    }
        
    listOfFileDOM(elements, path) {
        const list = [];
        const container = document.createElement("div");
        const ol = document.createElement("ol");

        container.className = "content";
        ol.className = "files";

        elements.forEach((filename) => {
            const ext = filename.toLowerCase().split(".");
            const li = document.createElement("li");
            li.id = "file";
            li.className = `file ${ext[ext.length - 1]}`;
            li.dataset.filename = filename;
            li.dataset.location = path;
            li.innerHTML = filename;
            li.addEventListener('click', this.handleClick.bind(this, filename, path));
            
            list.push(li);
        });
        ol.append(...list);
        container.appendChild(ol);
        
        return container;
    }

    /**
     * @param {String} dirName
     * Nombre del directorio
     * @param { String } listOfFileOrListOfDir
     * un string con los subdirectorios y/o archivos del directorio
     * @param { Boolean } isOpen
     * Permite tener un directorio abierto en el explorador de archivos
     */
    containerFilesDOM(dirName, listOfFileOrListOfDir, isOpen) {
        const details = document.createElement("details");
        const summary = document.createElement("summary");

        isOpen
            ? details.setAttribute("open", true)
            : details.setAttribute("open", false);

        summary.innerHTML = dirName;
        details.append(summary, listOfFileOrListOfDir);
        
        return details;
    }
}


export { ListDirTemplate }
