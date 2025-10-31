/// @symbolgeneration
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <map>
#include <mc/src-deps/core/headerIncludes/gsl_includes.hpp>
#include <amethyst/Imports.hpp>

class PackManifest;
class PackAccessStrategy;
class ResourcePackManager;
class ResourceLoadManager;
class I18nObserver;
class Localization;


class I18n {
public:
    virtual ~I18n();
    virtual void clearLanguages() = 0;
    virtual std::vector<std::string> findAvailableLanguages(ResourcePackManager&) = 0;
    virtual std::unordered_map<std::string, std::string> findAvailableLanguageNames(ResourcePackManager&) = 0;
    virtual void loadLanguages(ResourcePackManager&, gsl::not_null<Bedrock::NonOwnerPointer<ResourceLoadManager>>, const std::string&) = 0;
    virtual void loadAllLanguages(ResourcePackManager&) = 0;
    virtual std::vector<std::string> getLanguageCodesFromPack(PackAccessStrategy const&) = 0;
    virtual void loadLanguageKeywordsFromPack(PackManifest const&, PackAccessStrategy const&, std::vector<std::string> const&) = 0;
    virtual void loadLanguageKeywordsFromPack(PackManifest const&, PackAccessStrategy const&) = 0;
    virtual void appendLanguageStringsFromPack(PackManifest const&, std::multimap<std::string, std::pair<std::string, std::string>> const&) = 0;
    virtual std::unordered_map<std::string, std::string> getLanguageKeywordsFromPack(PackManifest const&, std::string const&) = 0;
    virtual void loadLanguagesByLocale(std::unordered_multimap<std::string, std::pair<std::string, std::string>> const&) = 0;
    virtual void appendAdditionalTranslations(std::unordered_map<std::string, std::string> const&, std::string const&) = 0;
    virtual void appendLanguageStrings(PackAccessStrategy*) = 0;
    virtual void addI18nObserver(I18nObserver&) = 0;
    virtual void chooseLanguage(std::string const&) = 0;
    virtual std::string get(std::string const&, std::shared_ptr<Localization> const) = 0;
    virtual std::string get(std::string const&, std::vector<std::string> const&, std::shared_ptr<Localization> const) = 0; // 128
    virtual std::string getPackKeywordValue(PackManifest const&, std::string const&) = 0;
    virtual std::string getPackKeywordValueForTelemetry(PackManifest const&, std::string const&) = 0;
    virtual bool hasPackKeyEntry(PackManifest const&, std::string const&) = 0;
    virtual std::vector<std::string> const& getSupportedLanguageCodes() = 0;
    virtual std::string const& getLanguageName(std::string const&) = 0;
    virtual std::shared_ptr<Localization> const getLocaleFor(std::string const&) = 0;
    virtual std::string const& getLocaleCodeFor(std::string const&) = 0;
    virtual gsl::not_null<std::shared_ptr<const Localization>> getCurrentLanguage() = 0;
    virtual bool languageSupportsHypenSplitting() = 0;
    virtual std::string getLocalizedAssetFileWithFallback(std::string const&, std::string const&) = 0;
    virtual bool isPackKeyword(std::string const&) = 0;
};

/// @signature {40 53 48 83 EC ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 0C C8 8B 04 0A 39 05 ? ? ? ? 7F ? 48 8D 05 ? ? ? ? 48 83 C4 ? 5B C3 48 8D 0D ? ? ? ? E8 ? ? ? ? 83 3D ? ? ? ? ? 75 ? 48 8D 1D ? ? ? ? 48 8B CB E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 90 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C3 48 83 C4 ? 5B C3 CC CC CC CC B0, win-server}
/// @signature {48 83 EC ? BA ? ? ? ? 65 48 8B 04 25 ? ? ? ? 48 8B 08 8B 04 0A 39 05 ? ? ? ? 7F ? 48 8D 05 ? ? ? ? 48 83 C4 ? C3 48 8D 0D ? ? ? ? E8 ? ? ? ? 83 3D ? ? ? ? ? 75 ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 90 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 83 C4 ? C3 CC CC CC CC CC 48 89 5C 24}
MC I18n& getI18n();

std::string operator"" _i18n(const char* str, size_t);

std::string i18n(const std::string& key);