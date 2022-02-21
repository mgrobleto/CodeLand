import { getCookie } from "/static/scripts/libs/cookies.js";
import ListDir from "./listDirUI/listDir.js";
import storage from './utils/storage.js'
import reducer from "./reducer/index.js";
import tabUI from "./tabUI/tab.js";

const data = window.__PRELOADED_STATE__;
const fragmentName = window.__FRAGMENT_NAME__;
const depthDir = window.__DIR_DEPTH__;

delete window.__PRELOADED_STATE__;
delete window.__FRAGMENT_NAME__;
delete window.__DIR_DEPTH__;

storage.createStore(reducer, [], fragmentName)

window.addEventListener("load", async () => {
    const project_id = getCookie('fragment_id')
    const response = await fetch(`/is-owner/fragment/${project_id}`);
    
    const isOwner = await response.json()
    console.log(isOwner)

    const listDir = new ListDir(data, fragmentName, depthDir, isOwner.success);
    listDir.renderList();
    tabUI.render(storage.getStore());
});
