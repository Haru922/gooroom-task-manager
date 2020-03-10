gooroom_task_manager_sources = [
    'gtm_main.c',
    'gtm_application.c',
    'gtm_window.c',
    'gtm_tree_view_model.c',
    'gtm_text_view_model.c',
    'gtm_common_util.c',
    'gtm_process.c',
]

gooroom_task_manager_deps = [
    dependency('gio-2.0', version: '>= 2.50'),
    dependency('gtk+-3.0', version: '>= 3.22'),
    dependency('libgtop-2.0', version: '>=2.37.0'),
    dependency('glib-2.0', version: '>=2.56.0'),
]

gnome = import('gnome')

gooroom_task_manager_sources += gnome.compile_resources('gooroom-task-manager-resources',
                                                'gtm.gresource.xml',
                                                c_name: 'gooroom_task_manager'
)

executable('gooroom-task-manager', gooroom_task_manager_sources,
           dependencies: gooroom_task_manager_deps,
           install: true,
)
