module.exports = {
    'GET /ajax': async(ctx, next) => {
        ctx.render('ajax.html', {
            title: 'ajax'
        });
    },
    'GET /ajax_test': async(ctx, next) => {
        ctx.response.body = "Success";
    }

}