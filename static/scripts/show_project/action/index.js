export const setTab = (tab) => {
    return {
        type: 'SET_TAB',
        payload: tab
    }
}

export const deleteTab = (key) => {
    return {
        type: 'DELETE_TAB',
        payload: key
    }
}

export const activeTab = (key) => {
    return {
        type: 'ACTIVE_TAB',
        payload: key
    }
}