# form_autocomplete
Drupal module to support controlled vocabulary autocomplete in metadata forms of the FLAT deposit UI
To allow for the autocomplete, please add the following to your metadata form xml, e.g. `Helpers/CMDI/FormTemplates/MPI_Bundle.xml`

```
<item id="fieldset_05" type="Composite" name="Content_Language" multival="true" inherited="true" minOccurrence="0">
    <title>Content Language</title>
    <type>fieldset</type>
    <container>Content Languages</container>
    <item id="field_17" name="Name" type="Leaf" inherited="true" minOccurrence="1">
        <title>Name</title>
        <type>textfield</type>
        <data>
            <role>flat-lang-autocomplete</role>
        </data>
    </item>
    <item id="field_18" name="Id" type="Leaf" inherited="true" minOccurrence="1">
        <title>Id</title>
        <type>textfield</type>
        <data>
            <role>flat-lang-autocomplete-destination</role>
        </data>
    </item>
</item>
```
