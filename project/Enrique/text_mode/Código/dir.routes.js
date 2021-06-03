const router = require('express').Router()
const fs = require('fs')
const path = require('path')

router.get('/:path?', async (req, res, next) => {
    console.log(req.url)
    try {
        const dirPath = path.resolve(process.cwd(), 'assets', 'uploads');
        const dir = await fs.promises.opendir(dirPath)
        const content = { files: [], directories: [] }

        for await (const dirent of dir) {
            if(dirent.isDirectory()) {
                content.directories.push(dirent.name)
            } else {
                content.files.push(dirent.name)
            }
        }
        content.directories.sort()
        content.files.sort()
        return res.json({path: dirPath, content, success: true})
    } catch(err) {
        next(err)
    }
    res.sendStatus(200)
})

module.exports = router