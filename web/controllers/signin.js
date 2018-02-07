module.exports = {
    'POST /signin': async(ctx, next) => {
        var
            email = ctx.request.body.email || '',
            passwd = ctx.request.body.passwd || '';
        if (email === 'sxn96@sina.com' && passwd === '123456') {
            console.log('signin ok');
            ctx.render('signin_success.html', { title: 'Sign In OK' });
        } else {
            console.log('signin failed');
            ctx.render('signin_fail.html', { title: 'Sign In Fail' });
        }

    }
}