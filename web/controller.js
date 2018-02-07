const fs = require('fs');

function addMapping(router, m) {
    for (var l in m) {
        if (l.startsWith('GET ')) {
            console.log(`precessing mapping ${l}`);
            router.get(l.substring(4), m[l]);
        } else if (l.startsWith('POST ')) {
            console.log(`precessing mapping ${l}`);
            router.post(l.substring(5), m[l]);
        } else {
            console.log('unknown url');
        }
    }
}

function addControllers(router, dir) {
    fs.readdirSync(__dirname + '/' + dir).filter((f) => {
        return f.endsWith('.js');
    }).forEach((f) => {
        var m = require(__dirname + '/' + dir + '/' + f);
        addMapping(router, m);
    })
}

module.exports = function(dir) {
    let router = require('koa-router')();
    let dirn = dir || 'controllers';
    addControllers(router, dirn);
    return router.routes();
}