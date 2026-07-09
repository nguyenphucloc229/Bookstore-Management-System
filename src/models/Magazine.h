#pragma once
#include "Product.h"


class Magazine : public Product {
public:
    Magazine(int id, const QString& name, double price, int stockQty,
             int issueNumber, const QString& publishDate);

    QString getType() const override { return "MAGAZINE"; }
    QString getDetails() const override;

    int issueNumber() const { return m_issueNumber; }
    QString publishDate() const { return m_publishDate; }

    void setIssueNumber(int v) { m_issueNumber = v; }
    void setPublishDate(const QString& v) { m_publishDate = v; }

private:
    int m_issueNumber;
    QString m_publishDate;
};
