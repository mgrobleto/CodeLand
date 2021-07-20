import { TabTemplates } from './templates.js'

class TabUI extends TabTemplates {
    constructor() {
        super()
        this.$containerTab = document.getElementById('editor-group')
    }
    
    render(tabs) {
        const tabArray = [] 
        
        tabs.forEach(tab => {
            tabArray.push(this.templateTab(tab))
        }
        )
        this.$containerTab.innerHTML = ''
        this.$containerTab.append(...tabArray)
    }
}

export default new TabUI();
