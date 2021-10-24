export default (state, action) => {

    switch (action.type) {
        case 'SET_TAB': {

            const exist = state.find(tab => tab.key === action.payload.key);
            if(exist){
                return state
            }
            state.forEach(tab => {
                tab.isActive = false;
            })
            state.push(action.payload)
            return state;
        }
        case 'DELETE_TAB': {
            return [...state.filter(tab => tab.key !== action.payload)]
        }
        case 'ACTIVE_TAB': {
            return [...state.map(tab => {
                if(tab.key !== action.payload) {
                    tab.isActive = false;
                } else {
                    tab.isActive = true;
                }
                return tab;
            })]
        }
        default:
            return state
    }
}