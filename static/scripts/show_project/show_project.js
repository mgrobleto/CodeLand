import { getCookie } from "/static/scripts/libs/cookies.js";
import ListDir from "./listDirUI/listDir.js";
import storage from './utils/storage.js'
import reducer from "./reducer/index.js";
import tabUI from "./tabUI/tab.js";

const data = window.__PRELOADED_STATE__;
const projectName = window.__PROJECT_NAME__;
const depthDir = window.__DIR_DEPTH__;

delete window.__PRELOADED_STATE__;
delete window.__PROJECT_NAME__;
delete window.__DIR_DEPTH__;

storage.createStore(reducer, [], projectName)

window.addEventListener("load", async () => {
    const project_id = getCookie('project_id')
    const response = await fetch(`/is-owner/${project_id}`);
    
    const isOwner = await response.json()
    console.log(isOwner)

    const listDir = new ListDir(data, projectName, depthDir, isOwner.success);
    listDir.renderList();
    tabUI.render(storage.getStore());
});
