module.exports = {
    'GET /map': async(ctx, next) => {
        ctx.render('map.html', {
            title: 'map'
        });
    }
}