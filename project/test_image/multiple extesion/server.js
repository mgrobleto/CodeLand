const application = require('./index')
require('./database/db')

application.listen(application.get('port'), function () {
    console.log(`Server on port ${application.get('port')}`)
})
