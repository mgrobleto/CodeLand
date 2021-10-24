"use strict";
import tabUI from "../tabUI/tab.js";
import storage from "../utils/storage.js";
import { setTab, deleteTab } from "../action/index.js";
import { getCookie } from "../../libs/cookies.js";
import { alertError } from '../../libs/alerts.js'

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

function deleteFile(div, path, filename) {
    const fragment_id = getCookie('fragment_id')

    const $buttonDelete = document.createElement("button");
    $buttonDelete.className = "btn btn-delete-file";
    $buttonDelete.innerHTML = `
    <svg width="16" height="16" alt="Borrar ${filename}" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
        <path d="M19 7L18.1327 19.1425C18.0579 20.1891 17.187 21 16.1378 21H7.86224C6.81296 21 5.94208 20.1891 5.86732 19.1425L5 7M10 11V17M14 11V17M15 7V4C15 3.44772 14.5523 3 14 3H10C9.44772 3 9 3.44772 9 4V7M4 7H20" stroke="#aaa" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
    </svg>
    `;

    div.appendChild($buttonDelete)
    
    $buttonDelete.addEventListener("click", async function() {
        const getStore = storage.getStore();
        const formData = new FormData();
        
        formData.append('filename', path + filename)
        console.log(path + filename)

        const response = await fetch(`/fragment/${fragment_id}`, {
            method: "DELETE",
            body: formData,
        })
        const responseJson = await response.json();
        
        console.log(responseJson)
        if(responseJson.success == true) {
            console.log(responseJson)
            div.remove()
            storage.dispatch(
                deleteTab(path + filename)
            )
            const tabRef = document.querySelector(`[data-ref="${path + filename}"]`)
            if(tabRef) {
                tabRef.remove()
            }
            tabUI.render(storage.getStore())
        } else {
            alertError(responseJson.message)
        }
    })
}

class ListDirTemplate {
    constructor() {
        this.listDir = [];
        this.$nodeStyle = null;
    }

    template(filesAndDirs, isOwner) {
        const template = new DocumentFragment();
        const path = getCookie('fragment_path') ? getCookie('fragment_path').replaceAll("\"", ""): null
        
        let content = 
        `
        <div class="container-project">
            <div class="project-name">
                <h1>${this.fragmentName}</h1>
            </div>
            <div class="project-content" id="project-content">
            </div>
        </div>
        `;
        content = new DOMParser().parseFromString(content, "text/html").querySelector(".container-project");
        template.appendChild(content);

        if(isOwner) {

            let addFile =
            `
                <div data-path-file="${path}" class="add-folder-or-file">
                    <input type="file" class="input-add-file" />
                    <button class="btn add-file">
                        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                            <path d="M9 13H15M12 10L12 16M17 21H7C5.89543 21 5 20.1046 5 19V5C5 3.89543 5.89543 3 7 3H12.5858C12.851 3 13.1054 3.10536 13.2929 3.29289L18.7071 8.70711C18.8946 8.89464 19 9.149 19 9.41421V19C19 20.1046 18.1046 21 17 21Z" stroke="#aaa" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                        </svg>
                    </button>
                </div>
            `
            addFile = new DOMParser().parseFromString(addFile, "text/html").querySelector('.add-folder-or-file');
            
            template.querySelector('.project-name').appendChild(addFile)

            addFile.querySelector(`.add-file`).addEventListener('click', (event) => {
                event.stopPropagation()
                // get before sibling 
                const $input = event.currentTarget.previousElementSibling;
                $input.click();
            })
            const $input = template.querySelector(`[data-path-file="${path}"] .input-add-file`)

            $input.addEventListener('change', async function() {
                const formData = new FormData()
                if($input.files) {
                    formData.append('file', $input.files[0], $input.files[0].name)
                    console.log($input.files[0].name)
                }
                const path = this.parentNode.dataset.pathFile
                const fragment_id = getCookie('fragment_id')

                console.log(path)
                formData.append('path', path)
                const response = await fetch(`/fragment/${fragment_id}`, {
                    method: 'POST',
                    body: formData
                })
                const data = await response.json()
                console.log(data)
                if(!data.success) {
                    console.log(data.message)
                    alertError(data.message)
                    return;
                }
                
                // Agrega una lista como la del método anterioe
                const ext = data.filename.toLowerCase().split(".");
                const containerList = document.createElement('div')
                const div = document.createElement('div')
                // const co
                const fileContainer = document.createElement("li");
                
                div.className = "container-file"
                containerList.className = 'files'
                // fileContainer.id = "file";
                fileContainer.className = `file ${ext[ext.length - 1]}`;
                fileContainer.dataset.filename = data.filename;
                fileContainer.dataset.location = path;
                fileContainer.innerHTML = data.filename;
                fileContainer.addEventListener(
                    "click",
                    handleClick.bind(this, data.filename, path)
                );
                if(isOwner) {
                    deleteFile(div, path, data.filename)
                }
                div.appendChild(fileContainer)
                const insertFile = document.querySelector('#mainFiles').children[0]
                insertFile.appendChild(div)
                fileContainer.click()  
            })

        }

        template.querySelector('#project-content').appendChild(filesAndDirs)

        return template;
    }

    listOfFileDOM(elements, path, isOwner, especialId = null) {
        const list = [];
        const container = document.createElement("div");
        const listFile = document.createElement("div");

        container.className = "content";
        listFile.className = "files";
        especialId && (container.id = especialId)

        elements.forEach((filename) => {
            const ext = filename.toLowerCase().split(".");
            const div = document.createElement("div");
            const fileContainer = document.createElement("div");
            const span = document.createElement("span");
            
            // li.id = "file";
            div.className = "container-file";
            fileContainer.className = `file ${ext[ext.length - 1]}`;
            span.className = 'file-filename';
            fileContainer.dataset.filename = filename;
            fileContainer.dataset.location = path;
            span.innerHTML = filename

            if(isOwner) {
                deleteFile(div, path, filename)
            }
            fileContainer.addEventListener(
                "click",
                handleClick.bind(this, filename, path)
                );
            fileContainer.appendChild(span);
            div.appendChild(fileContainer);

            list.push(div);
        });
        listFile.append(...list);
        container.appendChild(listFile);

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
        const template = new DocumentFragment();
        const details = document.createElement("details");
        const summary = document.createElement("summary");
    
        summary.innerHTML = dirName;
    
        isOpen && (details.open = true)
        
        details.append(summary, listOfFileOrListOfDir);
    
        if(isOwner) {
            const folderContainer = document.createElement("div");
    
            let actionFolder = 
            `
            <div class="add-folder-or-file" data-path-file="${path}">
                <input type="file" class="input-add-file" />
                <button class="btn btn-add add-file">
                    <svg width="22" height="22" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                        <path d="M9 13H15M12 10L12 16M17 21H7C5.89543 21 5 20.1046 5 19V5C5 3.89543 5.89543 3 7 3H12.5858C12.851 3 13.1054 3.10536 13.2929 3.29289L18.7071 8.70711C18.8946 8.89464 19 9.149 19 9.41421V19C19 20.1046 18.1046 21 17 21Z" stroke="#aaa" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                    </svg>
                </button>
                <button class="btn btn-add add-folder">
                    <svg width="22" height="22" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                        <path d="M9 13H15M12 10V16M3 17V7C3 5.89543 3.89543 5 5 5H11L13 7H19C20.1046 7 21 7.89543 21 9V17C21 18.1046 20.1046 19 19 19H5C3.89543 19 3 18.1046 3 17Z" stroke="#aaa" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                    </svg>                    
                </button>
            </div>
            `
            actionFolder = new DOMParser().parseFromString(actionFolder, "text/html").querySelector('.add-folder-or-file');
    
            folderContainer.className = 'folder-container'
            
            folderContainer.append(details, actionFolder);
            
            template.appendChild(folderContainer);
    
            // eventos para agregar archivos
            actionFolder.querySelector(`.add-file`).addEventListener('click', (event) => {
                event.stopPropagation()
                const $input = event.currentTarget.previousElementSibling;
                $input.click();
                // cuando le de click va a activar el input para seleccionar un archivo
            })
    
            const $input = actionFolder.querySelector(`.input-add-file`)
            
            $input.addEventListener('change', async function() {
                const formData = new FormData()
                if($input.files) {
                    formData.append('file', $input.files[0], $input.files[0].name)
                }
                const path = this.parentNode.dataset.pathFile
                const fragment_id = getCookie('fragment_id')
    
                formData.append('path', path)
                const response = await fetch(`/fragment/${fragment_id}`, {
                    method: 'POST',
                    body: formData
                })
                const data = await response.json()
                console.log(data)
                if(!data.success) {
                    console.log(data.message)
                    alertError(data.message)
                }
                
                // Agrega una lista como la del método anterioe
                const ext = data.filename.toLowerCase().split(".");
                const div = document.createElement('div')
                const fileContainer = document.createElement("li");
    
                div.className = "container-file"
                // fileContainer.id = "file";
                fileContainer.className = `file ${ext[ext.length - 1]}`;
                fileContainer.dataset.filename = data.filename;
                fileContainer.dataset.location = path;
                fileContainer.innerHTML = data.filename;
                fileContainer.addEventListener(
                    "click",
                    handleClick.bind(this, data.filename, path)
                );
                if(isOwner) {
                    deleteFile(div, path, data.filename)
                }
    
                div.appendChild(fileContainer);
                
                const children = [...details.children]
                children.forEach(element => {
                    if(element.classList.contains('content')) {
                        element.children[0].appendChild(div)
                    }
                })

                fileContainer.click()
            })
        } else {
            template.appendChild(details);
        }
    
        return template;
    }
}

export { ListDirTemplate };
