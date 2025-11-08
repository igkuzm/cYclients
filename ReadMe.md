# cYclients - Yclients API in C

First - get partner token in [Yclients developer](https://yclients.com/appstore/developers)

Then - create file partner_token.h with content:

```c
#define SETUP_PARTNER_TOKEN(partner_token) partner_token = \"your_token\";
```

Code example:

```c
char *user_token = NULL;
const CYCUser *user = NULL;
cyclients_login(login, password, &user, NULL);
if (user){
    printf("Authorized as: %s\n", user->name);
    user_token = user->user_token;

    // do your magick
}
```
