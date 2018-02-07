module.exports = {
    'GET /console': async(ctx, next) => {
        ctx.render('console.html', {
            title: '后台系统'
        });
    }
}