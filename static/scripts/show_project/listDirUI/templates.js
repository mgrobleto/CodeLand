"use strict";
import tabUI from "../tabUI/tab.js";
import storage from "../utils/storage.js";
import { setTab, deleteTab } from "../action/index.js";
import { getCookie } from "../../libs/cookies.js";

/**
 * @param {Array} elements
 * Nombres de los archivos del directorio
 * @param {Array} paths
 * La dirección del archivo en firebase
 * @returns { String }
 */
async function handleClick(filename, path) {
    const $showCode = document.querySelector("#show_code");
    const CURRENT_PATH = location.pathname;

    const file = {
        filename,
        path,
    };

    const response = await fetch(CURRENT_PATH, {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(file),
    });
    const responseJson = await response.json();

    if (responseJson.type == "code") {
        const store = storage.getStore();
        const key = path + filename;

        if (store) {
            if (store.find((tab) => tab.key === key)) {
                tabUI.render(storage.getStore(), key)
            } else {
                storage.dispatch(
                    setTab({
                        ...file,
                        key,
                        code: {
                            html: responseJson.code.html,
                            css: responseJson.code.css,
                        },
                        isActive: true,
                    })
                );
                tabUI.render(storage.getStore());
            }
        }
    } else {
        // let parse_binary = new Uint8Array(responseJson.file);
        console.log(responseJson)
        $showCode.innerHTML = `
            <img loading="lazy" src="${responseJson.image}" alt="${filename}" />
        `.trim();
    }
}

class ListDirTemplate {
    constructor() {
        this.listDir = [];
        this.$nodeStyle = null;
    }

    template(filesAndDirs) {
        const template = document.createElement("template");
        const path = getCookie('project_path') ? getCookie('project_path').replaceAll("\"", ""): null
        
        template.innerHTML = 
        `
            <div class="project-name">
                <h1>${this.projectName}</h1>
                <div class="add-folder-or-file" data-path="${path}">
                    <button class="btn">
                        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                            <path d="M9 13H15M12 10L12 16M17 21H7C5.89543 21 5 20.1046 5 19V5C5 3.89543 5.89543 3 7 3H12.5858C12.851 3 13.1054 3.10536 13.2929 3.29289L18.7071 8.70711C18.8946 8.89464 19 9.149 19 9.41421V19C19 20.1046 18.1046 21 17 21Z" stroke="#aaa" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                        </svg>

                    </button>
                    <button class="btn">
                        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                            <path d="M9 13H15M12 10V16M3 17V7C3 5.89543 3.89543 5 5 5H11L13 7H19C20.1046 7 21 7.89543 21 9V17C21 18.1046 20.1046 19 19 19H5C3.89543 19 3 18.1046 3 17Z" stroke="#aaa" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                        </svg>                    
                    </button>
                </div>
            </div>
            <div class="project-content" id="project-content">
            </div>
        `;

        template.content.querySelector('#project-content').appendChild(filesAndDirs)

        return template.content;
    }

    listOfFileDOM(elements, path, isOwner) {
        const list = [];
        const container = document.createElement("div");
        const ol = document.createElement("ol");

        container.className = "content";
        ol.className = "files";

        elements.forEach((filename) => {
            const ext = filename.toLowerCase().split(".");
            const li = document.createElement("li");
            const project_id = getCookie('project_id')
            // li.id = "file";
            li.className = `file ${ext[ext.length - 1]}`;
            li.dataset.filename = filename;
            li.dataset.location = path;
            li.innerHTML = filename
            if(isOwner) {
                const $buttonDelete = document.createElement("button");
                $buttonDelete.className = "btn btn-delete-file";
                $buttonDelete.innerHTML = `<img src="/static/icons/trash-icon.svg" alt="Borrar ${filename}" />`;
                li.appendChild($buttonDelete)
                $buttonDelete.addEventListener("click", async function() {
                    const formData = new FormData();
                    formData.append('filename', path + filename)
                    const response = await fetch(`/project/${project_id}`, {
                        method: "DELETE",
                        body: formData,
                    })
                    const responseJson = await response.json();
                    console.log(responseJson)
                    if(responseJson.success == true) {
                        console.log(responseJson)
                        this.parentNode.remove()
                        storage.dispatch(
                            deleteTab(path + filename)
                        )
                        const tabRef = document.querySelector(`[data-ref="${path + filename}"]`)
                        tabRef.children[1].innerHTML += 'ELIMINADO :C'
                    }
                })
            }
            li.addEventListener(
                "click",
                handleClick.bind(this, filename, path)
                );

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
    containerFilesDOM(dirName, path, listOfFileOrListOfDir, isOpen, isOwner) {
        const template = document.createElement('template')
        const details = document.createElement("details");
        const summary = document.createElement("summary");
        const name = document.createTextNode(dirName);

        if(isOwner) {
            template.innerHTML = `
                <div class="folder-container">
                    <div class="add-folder-or-file" data-path-file="${path}">
                        <input type="file" class="input-add-file" />
                        <button class="btn btn-add add-file">
                            <svg width="18" height="18" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                                <path d="M9 13H15M12 10L12 16M17 21H7C5.89543 21 5 20.1046 5 19V5C5 3.89543 5.89543 3 7 3H12.5858C12.851 3 13.1054 3.10536 13.2929 3.29289L18.7071 8.70711C18.8946 8.89464 19 9.149 19 9.41421V19C19 20.1046 18.1046 21 17 21Z" stroke="#aaa" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                            </svg>
                        </button>
                        <button class="btn btn-add">
                            <svg width="18" height="18" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                                <path d="M9 13H15M12 10V16M3 17V7C3 5.89543 3.89543 5 5 5H11L13 7H19C20.1046 7 21 7.89543 21 9V17C21 18.1046 20.1046 19 19 19H5C3.89543 19 3 18.1046 3 17Z" stroke="#aaa" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                            </svg>                    
                        </button>
                    </div>
                </div>
            `
        }

        isOpen
            ? details.setAttribute("open", true)
            : null;

        // summary.dataset.path = path;
        summary.appendChild(name)
        details.append(summary, listOfFileOrListOfDir);

        if(isOwner) {
            template.content.querySelector('.folder-container').insertBefore(details, template.content.querySelector('.folder-container').firstChild);
        } else {
            template.content.append(details);
        }

        if(isOwner) {
            template.content.querySelector(`[data-path-file="${path}"] .add-file`).addEventListener('click', (event) => {
                event.stopPropagation()
                // get before sibling 
                const $input = event.currentTarget.previousElementSibling;
                $input.click();
            })
            const $input = template.content.querySelector(`[data-path-file="${path}"] .input-add-file`)

            console.log(isOwner)
            $input.addEventListener('change', async function() {
                const formData = new FormData()
                if($input.files) {
                    formData.append('file', $input.files[0], $input.files[0].name)
                    console.log($input.files[0].name)
                }
                const path = this.parentNode.dataset.pathFile
                const project_id = getCookie('project_id')

                formData.append('path', path)
                const response = await fetch(`/project/${project_id}`, {
                    method: 'POST',
                    body: formData
                })
                const data = await response.json()
                console.log(data)
                if(!data.success) {
                    console.log(data.message)
                }
                const ext = data.filename.toLowerCase().split(".");
                const li = document.createElement("li");
                li.id = "file";
                li.className = `file ${ext[ext.length - 1]}`;
                li.dataset.filename = data.filename;
                li.dataset.location = path;
                li.innerHTML = data.filename;
                li.addEventListener(
                    "click",
                    handleClick.bind(this, data.filename, path)
                );
                const insertFile = document.querySelector(`[data-location="${path}"]`).parentNode
                insertFile.appendChild(li)
                li.click()
                
            })
        }

        return template.content;
    }
}

export { ListDirTemplate };
