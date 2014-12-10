Aim:

- All the user fields should have a "alterable privacy" checkbox.
- If this checkbox is ticked, $user should be presented with an additional checkbox on user edit forms to be able to make specific fields' values private.
- If this second checkbox is ticked for a field of a user, only uid=1 and herself should be able to view that field's value.

Steps of implementation:
1. Have a checkbox on admin/config/people/accounts/fields for each (user) field
   OR
   Have a checkbox on admin/config/people/accounts/fields/field_{$user_field_name}
The latter seems to be the easier way via a hook_form_FORM_ID_alter(), @see user_form_field_ui_field_edit_form_alter().

2. Store that checkbox's state in field instance settings.

3. Do not forget to remove a field's settings from the {user_field_privacy_value} table when a field is removed.

4. Depending on the state of the checkbox (the setting cames from field instance settings), add a checkbox to user/$uid/edit form.

5. Store that checkbox's state in the {user_field_privacy_value} table (fid, uid, private).

6. Do not forget to remove a field value's settings from the {user_field_privacy_value} table when a user is removed.

7. Do not forget to remove a field value's settings from the {user_field_privacy_value} table when the field is removed.

8. Depending on the state of the second checkbox (the setting cames from the {user_field_privacy_value} table (fid, uid, private)), hide that field from user/$uid page.

9. Publish.

10. TODO: Automated tests.
- Add a 'field_user_test' field to the user entity (remember the field ID#1, see below); check if the field's UI has the 'user_field_privacy' checkbox with the title t('Allow the user to hide this field\'s value by making it private.') at http://example.com/admin/config/people/accounts/fields/field_user_test/edit beneath the label textfield.
- After submitting the same form check if the field instance settings hold the state of the checkbox for field ID#1 (two checks for both the states).
- Add a 'field_user_test2' (its type and/or widget is not important, but remember the field ID#2, see below), enable its 'user_field_privacy' checkbox and check if the http://example.com/user/$uid/edit form has the 'user_field_privacy' checkbox with the title t('Private') beneath the field's widget itself.
- Add a 'field_user_test3' (its type and/or widget is not important, but remember the field ID#3, see below), do not enable its 'user_field_privacy' checkbox and check if the http://example.com/user/$uid/edit form does not have the 'user_field_privacy' checkbox with the title t('Tick this if you want to hide this value from non-administrators.') beneath the field's widget itself.
- Create a user (and remember her uid#1, see below) and check if {user_field_privacy_value} is populated for uid = hers and fid = field ID#2.
- Remove the 'field_user_test2' field and check if the {user_field_privacy_value} table does not have any values for fid = field ID#2.
- Remove the user with uid = uid#1 and check if the {user_field_privacy_value} table does not have any values for uid = uid#1.
- Load the form available at http://example.com/admin/config/people/accounts/fields/field_user_test3/edit and check if the 'user_field_privacy' checkbox with the title t('Allow the user to hide this field\'s value by making it private.') is not ticked by default.
- Tick that checkbox and submit the form, then check if the field instance settings have privacy = 1 where for field ID#3.
- Create a user (and remember her uid#2, see below) with the 'user_field_privacy' checkbox for the 'field_user_test3' field ticked and the 'field_user_test3' itself filled with data, and check if the {user_field_privacy_value} has the row private = 1 where uid = uid#2 and fid = field ID#3.
- Check if anonymous does not see the contents of the 'field_user_test3' field for uid = uid#2 at http://example.com/user/$uid#2
- Check if user with uid = uid#2 does see the contents of the 'field_user_test3' field for uid = uid#2 at http://example.com/user/$uid#2
- Create a role with the 'access private fields' permission (and remember its rid#1, see below); create a user (and remember her uid#3, see below) in this role, and check if the user with uid = uid#3 does see the contents of the 'field_user_test3' field for uid = uid#2 at http://example.com/user/$uid#2
- Revoke the 'access private fields' from the role with rid = rid#1 and check if the user with uid = uid#3 does not see the contents of the 'field_user_test3' field for uid = uid#2 at http://example.com/user/$uid#2
- Uncheck the 'user_field_privacy' checkbox at the form available at http://example.com/admin/config/people/accounts/fields/field_user_test3/edit and check if if the user with uid = uid#3 does see the contents of the 'field_user_test3' field for uid = uid#2 at http://example.com/user/$uid#2
- Check if the user_field_privacy setting for any given user field is exported properly (two checks for both the states of any of the checkboxes), eg. via features.module.
- Check anything else I may have forgotten. :)

BUGS:
None known.
