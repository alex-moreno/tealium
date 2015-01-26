Tealium is an API which allows third party apps to add its own tags into the site.
The module itself does not do anything, you need to develop your own integration,
although a Tealium UI for some basic stuff is planned at some point.

##Adding new tags.

Tealium uses hook_tealium_tags to communicate the new tags we want to add to a
new page. Let’s say for example we are working in a module, called my_module.
In my_module.module we’ll have a function like that:

```
function my_module_tealium_tags() {
  return $tags;
}
```

Where tags will be an array with the tags that we want to populate.
For example:

```
  $tags['pageTemplate'] = 'My Template';
```